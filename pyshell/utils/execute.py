#!/usr/bin/env python3

import utils.global_var as gv
import utils.execution.variables as variables_mod
import utils.execution.job_control as control
import utils.execution.tmpsh_signal as tmpsh_signal
import utils.execution.fd_management as fd
import utils.execution.redirection as redirection
import utils.execution.file as file
import utils.execution.forker as forker
import utils.execution.foreground as fg
from utils.execution.exec_command import exec_command
import sys
import os
import time
import signal
import termios

from utils.global_var import dprint

#To do:
# - Check where I'm loosing time with multiple CMDSUBST
# - Check escapement (check Enzo who wanted to change tag for variables)
# - Unable to run "echo ok > $(echo x) > $(echo y)"

def timer(function):
    def time_wrapper(*args, **kwargs):
        start = time.clock()
        res = function(*args, **kwargs)
        end = time.clock()
        dprint("total time for {} = {}".format(function.__name__, end - start))
        return res
    return time_wrapper

class Executor:
    """From an AST, run each command"""
    def __init__(self, ast):
        ast.get_command()
        self.run_ast(ast)


    def run_ast(self, ast):
        """
        Main function to run an entire AST instance in a 
        recursive way.
        Go through each branch and run them one by one (or more),
        running each time the contained command.
        """
        index = 0
        nbr_branch = len(ast.list_branch)
        job_list = []
        while index < nbr_branch:
            branch = ast.list_branch[index]
            job_list.append(branch)
            variables_mod.replace_variable(branch)
            if self.check_andor(branch) == False:
                index = self.find_newstart(nbr_branch, index, ast)
                job_list.clear()
                continue
            self.perform_subast_replacement(branch)
            branch.pgid = job_list[0].pgid
            res = self.check_background(ast.list_branch, index)
            #Prepare piping, store stdin pipe for the next command
            if branch.tag_end == "PIPE":
                ast.list_branch[index + 1].stdin, branch.stdout = fd.setup_pipe_fd()
            if self.perform_command_as_subast(branch) == False:
                exec_command(branch)
            self.close_subast_pipe(branch)
            self.analyse_branch_result(branch, job_list)
            index += 1
        gv.JOBS.wait_zombie()
    
    ##################################################################
    ##                  Utils for self.run_ast                      ##
    ##################################################################

    def analyse_branch_result(self, branch, job_list):
        """
        Whenever a branch have been executed, behave depending of the branch
        configuration.
        Wait the child process if needed, add the current jobs_list in
        background otherwise.
        Retrieve the foreground for the shell if possible.
        """
        self.try_set_job_pgid(job_list)
        if branch.tag_end == "BACKGROUND_JOBS":
            gv.LAST_STATUS = 0
            gv.JOBS.add_job(job_list)
        elif branch.tag_end != "PIPE":
            if control.analyse_job_status(job_list) == control.WaitState.RUNNING:
                gv.JOBS.add_job(job_list)
            if branch.background == False and gv.JOBS.allow_background == True:
                fg.set_foreground(os.getpgrp())
                fg.restore_tcattr()
            gv.LAST_STATUS = branch.status
        if branch.tag_end != "PIPE":
            job_list.clear()

    def try_set_job_pgid(self, job_list):
        """
        From a given list, try to set up his pgid for each
        job whenever a pid is available.
        Avoid to search pgid if already set.
        """
        if job_list[0].pgid != 0:
            return
        index = 0
        nbr_job = len(job_list)
        pgid = 0
        #Try to find the first available pid and get his pgid.
        while index < nbr_job and pgid == 0:
            job = job_list[index]
            if job.pid is not None:
                pgid = os.getpgid(job.pid)
            index += 1

        #If no pgid available (only jobs with builtin),
        #keep pgid set to 0 by doing nothing
        if pgid == 0:
            return
        #Set up the pgid to the entire list otherwise
        index = 0
        while index < nbr_job:
            job = job_list[index]
            job.pgid = pgid
            index += 1


    def close_subast_pipe(self, branch):
        """
        Go through each subast of the the branch, and for each CMDSUBST,
        close the AST.link_fd attribute, who his the fd to read/write
        with the CMDSUBST.
        """
        index = 0
        nbr_subast = len(branch.subast)
        while index < nbr_subast:
            subast = branch.subast[index]
            if subast.type.startswith("CMDSUBST"):
                os.close(subast.link_fd)
            elif subast.type == "DQUOTES":
                self.close_subast_pipe(subast.list_branch[0])
            index += 1

    def check_background(self, list_branch, index):
        """
        Check if the branch have to be run in background or
        in foreground.
        If it's pipe, check the last element of the pipeline to
        see the behavior to apply.
        """
        branch = list_branch[index]
        if branch.background == True:
            return True
        elif branch.tag_end == "BACKGROUND_JOBS":
            branch.background = True
            return True
        elif gv.JOBS.allow_background == False:
            return False
        elif branch.tag_end == "PIPE":
            list_branch[index + 1].pgid = branch.pgid
            branch.background = self.check_background(list_branch, index + 1)
            return branch.background
        return False

    def find_newstart(self, max_len, index, ast):
        """
        Whenever a command combination is over with CMDAND or CMDOR,
        skip the set until the next terminator
        """
        while index < max_len:
            branch = ast.list_branch[index]
            if branch.tag_end in ["END_COMMAND", "BACKGROUND_JOBS"]:
                return index + 1
            index += 1
        return index

    def check_andor(self, branch):
        """
        Check if the command have to be run according to last status.
        True if we have to run the command, false otherwise.
        """
        if branch.begin_andor == "":
            return True
        if branch.begin_andor == "CMDAND" and gv.LAST_STATUS == 0:
            return True
        elif branch.begin_andor == "CMDOR" and gv.LAST_STATUS != 0:
            return True
        return False


    ##################################################################
    ##          Functions to run a branch's subast list             ##
    ##################################################################

    def run_cmdsubst(self, subast):
        """
        Fork and prepare a subshell for CMDSUBT replacement.
        Prepare the right subshell configuration, blocking job control.
        Replace stdin/stdout apropriately.
        Link to the subast his pid and filedescriptor.
        """
        pipe_fd = fd.setup_pipe_fd()
        pid = forker.fork_prepare(os.getpgrp(), background=False)
        if pid == 0:
            #Remove parent background jobs
            gv.JOBS.clear()
            gv.JOBS.allow_background = False
            gv.CEXTENSION.change_sigmask(signal.SIGTSTP, signal.SIG_BLOCK)
            #Select fd to use as stdin/stdout depending of the subst type
            stdin = stdout = None
            if subast.type == "CMDSUBST2":
                stdin = pipe_fd.pop(0)
            elif subast.type in ["CMDSUBST1", "CMDSUBST3"]:
                stdout = pipe_fd.pop(1)
            fd.replace_std_fd(stdin, stdout)
            os.close(pipe_fd[0])
            self.run_ast(subast)
            exit(gv.LAST_STATUS)
        else:
            subast.pid = pid
            subast.link_fd = pipe_fd.pop(1) if subast.type == "CMDSUBST2" \
                    else pipe_fd.pop(0)
            os.close(pipe_fd[0])

    def prepare_cmd_subst(self, branch):
        """
        For each CMDSUBST[123] or DQUOTES, run in a subshell his ast representation.
        Do not wait any of those subprocess.
        """
        index = 0
        nbr_subast = len(branch.subast)
        while index < nbr_subast:
            subast = branch.subast[index]
            if subast.type.startswith("CMDSUBST"):
                self.run_cmdsubst(subast)
            elif subast.type == "DQUOTES":
                self.prepare_cmd_subst(subast.list_branch[0])
            index += 1

    def replace_subast(self, branch, change_index, content):
        """
        Replace in a branch the content given by a subast with
        a CMDSUBT[123].
        Try to replace this content in the tagstokens list of the branch,
        or replace in the filedescriptor list if it's not found.
        """
        index = 0
        while index < branch.tagstokens.length:
            tag = branch.tagstokens.tags[index]
            token = branch.tagstokens.tokens[index]
            if tag == "SUBAST" and int(token) == change_index:
                branch.tagstokens.tokens[index] = content
                branch.tagstokens.tags[index] = "STMT"
                return None
            index += 1
        #If this point is reached, try to replace subast for filedescriptor
        nbr_redirection = len(branch.redirectionfd)
        index = 0
        while index < nbr_redirection:
            redirection = branch.redirectionfd[index]
            tag = redirection.tagstokens.tags[0]
            token = redirection.tagstokens.tokens[0]
            if tag == "SUBAST" and int(token) == change_index:
                redirection.dest = content
            index += 1

    def perform_subast_replacement(self, branch):
        """
        Inside a branch, replace each subast element by the generated content
        or the cmdsubst /dev/fd file.
        """
        self.prepare_cmd_subst(branch)
        index = 0
        nbr_ast = len(branch.subast)
        while index < nbr_ast:
            subast = branch.subast[index]
            if subast.type == "QUOTE":
                content = "".join(subast.list_branch[0].tagstokens.tokens)
            elif subast.type == "CMDSUBST1":
                content = file.read_fd(subast.link_fd)
                os.waitpid(subast.pid, os.WUNTRACED)
                if len(content) > 0 and content[-1] == '\n': #SHOULD NOT BE DONE, need one more tokenisation
                    content = content[:-1]
            elif subast.type in ["CMDSUBST2", "CMDSUBST3"]:
                content = "/dev/fd/" + str(subast.link_fd)
            elif subast.type == "BRACEPARAM":
                var = subast.list_branch[0].tagstokens.tokens[0]
                content = variables_mod.retrieve_variable(var)
            elif subast.type == "DQUOTES":
                self.perform_subast_replacement(subast.list_branch[0])
                content = "".join(subast.list_branch[0].tagstokens.tokens)
            if subast.type in ["BRACEPARAM", "CMDSUBST1","CMDSUBST2","CMDSUBST3","QUOTE", 
                    "DQUOTES"]:
                self.replace_subast(branch, index, content)
            index += 1

    ##################################################################
    ##      Command runner with execve or from ast + utils          ##
    ##################################################################
    
    def run_subshell(self, branch, subast):
        """
        From a given ast, run the command in a subshell.
        Redirect stdin and/or stdout if given.
        Wait the subshell and catch his return value if expected.
        """
        #NEED TO WAIT ALL KIND OF SUBSHELL
        pid = forker.fork_prepare(branch.pgid, branch.background)
        if pid == 0:
            redirection.setup_redirection(branch)
            tmpsh_signal.reset_signals()
            gv.JOBS.clear()
            gv.JOBS.allow_background = False
            fd.replace_std_fd(branch.stdin, branch.stdout)
            self.run_ast(subast)
            exit(gv.LAST_STATUS)
        else:
            fd.close_fds([branch.stdin, branch.stdout, -1])
            return pid

    def perform_command_as_subast(self, branch):
        """
        If the command is composed of a SUBSH or a CURSH,
        create a layer for this kind of command and run them.
        If it's not run in a subshell, save and restore the initial 
        stdin/stdout/stderr to prevent change during execution.
        """
        index = 0
        nbr_subast = len(branch.subast)
        while index < nbr_subast:
            subast = branch.subast[index]
            if subast.type in ["SUBSH", "CURSH"]:
                if subast.type == "CURSH" and branch.tag_end not in ["PIPE", "BACKGROUND_JOBS"]:
                    saved_std_fd = fd.save_std_fd()
                    fd.replace_std_fd(branch.stdin, branch.stdout)
                    redirection.setup_redirection(branch)
                    self.run_ast(subast)
                    branch.pid = None
                    fd.restore_std_fd(saved_std_fd)
                else:
                    pid = self.run_subshell(branch, subast)
                    branch.pid = pid
                return True
            index += 1
        return False
