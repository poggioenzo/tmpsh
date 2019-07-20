#!/usr/bin/env python3

from utils.tagstokens import TagsTokens as Token
import utils.global_var as gv
import utils.execution.environ as environ
import utils.builtins as builtins
import utils.execution.job_control as control
import utils.execution.tmpsh_signal as tmpsh_signal
import utils.execution.fd_management as fd
import utils.execution.redirection as redirection
import utils.execution.file as file
import fcntl
import sys
import os
import time
import signal
import termios

from utils.global_var import dprint

#To do:
# - Upgrade analyse_status

def timer(function):
    def time_wrapper(*args, **kwargs):
        start = time.clock()
        res = function(*args, **kwargs)
        end = time.clock()
        dprint("total time for {} = {}".format(function.__name__, end - start))
        return res
    return time_wrapper

def push_shell_foreground():
    """
    Try to retrieve the foreground for the shell if
    """
    if os.tcgetpgrp(sys.stdin.fileno()) == os.getpgrp():
        os.tcsetpgrp(sys.stdin.fileno(), os.getpgrp())
        termios.tcsetattr(sys.stdin.fileno(), termios.TCSADRAIN, gv.TCSETTINGS)

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
            self.replace_variable(branch)
            if self.check_andor(branch) == False:
                index = self.find_newstart(nbr_branch, index, ast)
                job_list.clear()
                continue
            self.perform_subast_replacement(branch)
            branch.pgid = self.check_pgid(job_list)
            res = self.check_background(ast.list_branch, index)
            #Prepare piping, store stdin pipe for the next command
            if branch.tag_end == "PIPE":
                ast.list_branch[index + 1].stdin, branch.stdout = fd.setup_pipe_fd()
            if self.perform_command_as_subast(branch) == False:
                self.exec_command(branch)
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
        if branch.tag_end == "BACKGROUND_JOBS":
            gv.LAST_STATUS = 0
            gv.JOBS.add_job(job_list)
        elif branch.tag_end != "PIPE":
            if control.analyse_job_status(job_list) == control.WaitState.RUNNING:
                gv.JOBS.add_job(job_list)
            if branch.background == False and gv.JOBS.allow_background == True:
                os.tcsetpgrp(sys.stdin.fileno(), os.getpgrp())
                termios.tcsetattr(0, termios.TCSADRAIN, gv.TCSETTINGS)
            if branch.status is not None:
                gv.LAST_STATUS = branch.status
        if branch.tag_end != "PIPE":
            job_list.clear()

    def close_subast_pipe(self, branch):
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

    def check_pgid(self, job_list):
        """
        Verify if the current branch have to use the pipeline
        pgid.
        """
        nbr_job = len(job_list)
        if nbr_job == 1:
            return 0
        index = 0
        while index < nbr_job:
            job = job_list[index]
            if job.pgid != 0:
                return job.pgid
            if job.pid != None:
                return os.getpgid(job.pid)
            index += 1
        return 0

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

    def replace_variable(self, branch):
        """
        Replace each variable within a single branch.
        Make a recursive calling if there is any dquotes element inside
        the branch.
        """
        index = 0
        index_subast = 0
        while index < branch.tagstokens.length:
            tag = branch.tagstokens.tags[index]
            token = branch.tagstokens.tokens[index]
            if tag == "STMT" and token[0] == "$":
                variable = environ.retrieve_variable(token[1:])
                branch.tagstokens.tokens[index] = variable
            elif tag == "SUBAST":
                if branch.subast[index_subast].type == "DQUOTES":
                    self.replace_variable(branch.subast[index_subast].list_branch[0])
                index_subast += 1
            index += 1

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
        pid = self.fork_prepare(os.getpgrp(), background=False)
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

    def replace_ast_tag(self, branch):
        """
        For each subast, replace in the current branch the subast tag by
        the STMT tag, to have only STMT to create command.
        """
        index = 0
        pos_subast = 0
        while index < branch.tagstokens.length:
            tag = branch.tagstokens.tags[index]
            if tag == "SUBAST":
                if branch.subast[pos_subast].type in \
                        ["DQUOTES", "QUOTE", "CMDSUBST1", "CMDSUBST2", "CMDSUBST3", "BRACEPARAM"]:
                    branch.tagstokens.tags[index] = "STMT"
                pos_subast += 1
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
                content = environ.retrieve_variable(var)
            elif subast.type == "DQUOTES":
                self.perform_subast_replacement(subast.list_branch[0])
                content = "".join(subast.list_branch[0].tagstokens.tokens)
            if subast.type in ["BRACEPARAM", "CMDSUBST1","CMDSUBST2","CMDSUBST3","QUOTE", 
                    "DQUOTES"]:
                self.replace_subast(branch, index, content)
            index += 1
        self.replace_ast_tag(branch)

    ##################################################################
    ##      Command runner with execve or from ast + utils          ##
    ##################################################################
    
    def retrieve_assignation(self, branch):
        """
        Find the list of assignation containing in the tagstokens.
        Return a list of tuples as [(key, mode, value), (...)]
        """
        assignation_list = []
        last_stmt = None
        index = 0
        tagstok = branch.tagstokens
        index_to_del = 0
        while True and index < tagstok.length:
            if last_stmt == None and tagstok.tags[index] == "STMT":
                last_stmt = tagstok.tokens[index]
            elif tagstok.tags[index] in ["CONCATENATION", "ASSIGNATION_EQUAL"]:
                index_to_del = index + 2 if tagstok.tags[index + 1] == "SPACE" else index + 1
                assignation_list.append((last_stmt, tagstok.tags[index], tagstok.tokens[index_to_del]))
                index = index_to_del
                last_stmt = None
            index += 1
        if len(assignation_list) > 0:
            del tagstok.tags[:index_to_del + 1]
            del tagstok.tokens[:index_to_del + 1]
        tagstok.update_length()
        return assignation_list

    def variables_config(self, variables, only_env=False):
        """
        Facility to set the variables list [(key, mode, value), (...)] according
        to his key=value. The mode specify if it is
        a CONCATENATION or an ASSIGNATION_EQUAL.
        Set up the variable only to the environnement if specified.
        """
        nbr_var = len(variables)
        index = 0
        while index < nbr_var:
            variable_data = variables[index]
            mode = variable_data[1]
            key = variable_data[0]
            value = variable_data[2]
            environ.update_var(key, value, mode, only_env)
            index += 1

    def run_subshell(self, branch, subast):
        """
        From a given ast, run the command in a subshell.
        Redirect stdin and/or stdout if given.
        Wait the subshell and catch his return value if expected.
        """
        #NEED TO WAIT ALL KIND OF SUBSHELL
        pid = self.fork_prepare(branch.pgid, branch.background)
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
                    self.run_ast(subast)
                    branch.pid = None
                    fd.restore_std_fd(saved_std_fd)
                else:
                    pid = self.run_subshell(branch, subast)
                    branch.pid = pid
                return True
            index += 1
        return False

    def fork_prepare(self, pgid=0, background=True):
        """
        Fork a new process, and prepare the process to be in foreground
        or in background.
        """
        pid = os.fork()
        if gv.JOBS.allow_background == True:
            os.setpgid(pid, pgid)
            if background == False:
                os.tcsetpgrp(sys.stdin.fileno(), os.getpgid(pid))
        return pid

    

    def child_execution(self, branch, argv, variables):
        if argv[0] in ["jobs", "fg", "cd", "umask"]:
            branch.status = self.run_builtin(argv, variables)
            return None
        pid = self.fork_prepare(branch.pgid, branch.background)
        if pid == 0:
            #restore all signals for the child
            tmpsh_signal.reset_signals()
            fd.replace_std_fd(branch.stdin, branch.stdout)
            redirection.setup_redirection(branch)
            self.variables_config(variables, only_env=True)
            executable = file.get_execname(argv[0])
            if executable == None:
                exit(127)
            os.execve(executable, argv, gv.ENVIRON)
        else:
            fd.close_fds([branch.stdin, branch.stdout, -1])
            return pid

    def exec_command(self, branch):
        """
        Use to run a simple command, the branch element which is not
        a SUBSH or a CURSH.
        Prepare command variables, run within the shell if the command is a
        builtin, fork otherwise if it's needed.
        Manage command filedescriptors/pipes.
        """
        variables = self.retrieve_assignation(branch)
        cmd_args = self.extract_cmd(branch)
        #Check if the command is only an assignation
        if len(cmd_args) == 0:
            fd.close_fds([branch.stdin, branch.stdout, -1])
            if len(variables) >= 1:
                self.variables_config(variables)
                branch.status = 0
            return
        branch.pid = self.child_execution(branch, cmd_args, variables)

    def run_builtin(self, cmd_args, variables):
        cmd = "builtins.{}({}, {})".format(cmd_args[0], cmd_args[1:],\
                dict(os.environ))
        return exec(cmd)

    def join_stmt(self, branch):
        """If a STMT is following an other STMT, concat them in a single token."""
        index = 0
        tagstok = branch.tagstokens
        while index < tagstok.length:
            if tagstok.tags[index] == "STMT":
                #Join with the previous STMT if needed
                if index > 0 and tagstok.tags[index - 1] == "STMT":
                    new_stmt = tagstok.tokens[index - 1] + tagstok.tokens[index]
                    tagstok.tokens[index - 1:index + 1] = [new_stmt]
                    del tagstok.tags[index]
                    tagstok.update_length()
                    index -= 1
            index += 1

    def extract_cmd(self, branch):
        """Get only token used to run a command, format argv + environ"""
        self.join_stmt(branch)
        command = []
        for index in range(branch.tagstokens.length):
            if branch.tagstokens.tags[index] in gv.GRAMMAR.grammar["STMT"]:
                command.append(branch.tagstokens.tokens[index])
        return command
