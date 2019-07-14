#!/usr/bin/env python3

from utils.tagstokens import TagsTokens as Token
import utils.global_var as gv
import utils.environ as environ
import utils.builtins as builtins
import utils.job_control as control
import utils.tmpsh_signal as tmpsh_signal
import utils.file as file
import utils.tmpsh_signal
import fcntl
import sys
import os
import time
import signal
import termios

#DEBUG = open("/dev/pts/7", "w")
def dprint(string, *args, **kwargs):
    print(string, *args, file=DEBUG, **kwargs)

def timer(function):
    def time_wrapper(*args, **kwargs):
        start = time.clock()
        res = function(*args, **kwargs)
        end = time.clock()
        return res
    return time_wrapper

def get_execname(cmd):
    cmd = cmd.strip() # ! Get space in STMT with PIPE
    if "/" in cmd:
        return cmd
    exec_folders = os.environ["PATH"]
    for folder in exec_folders.split(":"):
        execname = os.path.join(folder, cmd)
        if os.path.isfile(execname):
            return execname
    return None

def setup_pipe_fd():
    """
    Create pipe fds, and configure them to be inheritable
    and start only from RANGE_START.
    """
    RANGE_START = 63
    #Change fd value to get fd in range of [63:infinite[
    pipe_fd = list(os.pipe())
    old_pipe = pipe_fd.copy()
    pipe_fd[0] = fcntl.fcntl(pipe_fd[0], fcntl.F_DUPFD, RANGE_START)
    pipe_fd[1] = fcntl.fcntl(pipe_fd[1], fcntl.F_DUPFD, RANGE_START)
    os.set_inheritable(pipe_fd[0], True)
    os.set_inheritable(pipe_fd[1], True)
    os.close(old_pipe[0])
    os.close(old_pipe[1])
    return pipe_fd

def replace_fd(expected_fd, old_fd):
    """
    Replace an fd by the expected fd.
    Close the extra fd.
    """
    os.dup2(expected_fd, old_fd)
    os.close(expected_fd)

def replace_std_fd(stdin=None, stdout=None):
    """
    Replace two given fd to be current stdout and/or stderr.
    """
    if stdin:
        replace_fd(stdin, sys.stdin.fileno())
    if stdout:
        replace_fd(stdout, sys.stdout.fileno())

def close_fds(fd_list):
    """
    Close all fds in the given list. The list must end with -1.
    """
    index = 0
    while fd_list[index] != -1:
        if fd_list[index] is not None:
            os.close(fd_list[index])
        index += 1

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
                ast.list_branch[index + 1].stdin, branch.stdout = setup_pipe_fd()
            if self.perform_command_as_subast(job_list) == False:
                self.exec_command(job_list)
            if branch.tag_end == "BACKGROUND_JOBS":
                gv.LAST_STATUS = 0
                gv.JOBS.add_job(job_list)
            elif branch.tag_end != "PIPE":
                if control.analyse_job_status(job_list) == control.WaitState.RUNNING:
                    gv.JOBS.add_job(job_list)
                if branch.background == False:
                    os.tcsetpgrp(sys.stdin.fileno(), os.getpgrp())
                    termios.tcsetattr(0, termios.TCSANOW, gv.TCSETTINGS) #termios.TCSADRAIN
                gv.LAST_STATUS = branch.status
            if branch.tag_end != "PIPE":
                job_list.clear()
            index += 1
        gv.JOBS.wait_zombie()
    
    ##################################################################
    ##                  Utils for self.run_ast                      ##
    ##################################################################

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
        elif os.tcgetpgrp(sys.stdin.fileno()) not in [os.getpgrp(), branch.pgid]:
            branch.background = True
            return True
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

    def run_subshell(self, ast, stdin, stdout, pgid=0, background=False):
        """
        From a given ast, run the command in a subshell.
        Redirect stdin and/or stdout if given.
        Wait the subshell and catch his return value if expected.
        """
        #NEED TO WAIT ALL KIND OF SUBSHELL
        pid = self.fork_prepare(pgid, background)
        if pid == 0:
            gv.JOBS.clear()
            replace_std_fd(stdin, stdout)
            self.run_ast(ast)
            exit(gv.LAST_STATUS)
        else:
            close_fds([stdin, stdout, -1])
            return pid

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
                pipe_fd = setup_pipe_fd()
                subst_pipe = [None, None]
                if subast.type == "CMDSUBST2":
                    subst_pipe[0] = pipe_fd[0]
                elif subast.type in ["CMDSUBST1", "CMDSUBST3"]:
                    subst_pipe[1] = pipe_fd[1]
                #NEED TO WAIT SUBSHELL
                subast.pid = self.run_subshell(subast, *subst_pipe)
                subast.link_fd = pipe_fd[1] if subast.type == "CMDSUBST2" else pipe_fd[0]
            elif subast.type == "DQUOTES":
                self.prepare_cmd_subst(subast.list_branch[0])
            index += 1

    def save_std_fd(self):
        """
        Save actual stdin/stdout/stderr by duplicating their fd, 
        to be able to retore them further.
        """
        #Save standard fds stdin/stdout/stderr
        #CLOEXEC is set to avoid children to get those fds
        saved_stdin = fcntl.fcntl(0, fcntl.F_DUPFD_CLOEXEC, 100)
        saved_stdout = fcntl.fcntl(1, fcntl.F_DUPFD_CLOEXEC, 100)
        saved_stderr = fcntl.fcntl(2, fcntl.F_DUPFD_CLOEXEC, 100)
        return [saved_stdin, saved_stdout, saved_stderr]

    def restore_std_fd(self, std_fds):
        """
        From saved stdin/stdout/stderr of self.saved_std_fd, restore the
        each fds.
        """
        replace_fd(std_fds[0], sys.stdin.fileno())
        replace_fd(std_fds[1], sys.stdout.fileno())
        replace_fd(std_fds[2], sys.stderr.fileno())


    def replace_subast(self, branch, change_index, content):
        """Replace in a tagstoken list the content given by the subast"""
        index = 0
        pos_subast = 0
        while index < branch.tagstokens.length and pos_subast <= change_index:
            tag = branch.tagstokens.tags[index]
            if tag == "SUBAST":
                if change_index == pos_subast:
                    branch.tagstokens.tokens[index] = content
                pos_subast += 1
            index += 1
        pass

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
                os.waitpid(subast.pid, 0)
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

    def perform_command_as_subast(self, job_list):
        """
        If the command is composed of a SUBSH or a CURSH,
        create a layer for this kind of command and run them.
        Save and restore the initial stdin/stdout/stderr to
        prevent change during execution.
        """
        index = 0
        nbr_subast = len(job_list[-1].subast)
        while index < nbr_subast:
            subast = job_list[-1].subast[index]
            if subast.type in ["SUBSH", "CURSH"]:
                if subast.type == "CURSH" and job_list[-1].tag_end not in ["PIPE", "BACKGROUND_JOBS"]:
                    saved_std_fd = self.save_std_fd()
                    replace_std_fd(job_list[-1].stdin, branch.stdout)
                    self.run_ast(subast)
                    job_list[-1].pid = None
                    self.restore_std_fd(saved_std_fd)
                else:
                    pid = self.run_subshell(subast, job_list[-1].stdin, job_list[-1].stdout, \
                        job_list[-1].pgid, job_list[-1].background)
                    job_list[-1].pid = pid
                return True
            index += 1
        return False

    def fork_prepare(self, pgid=0, background=True):
        """
        Fork a new process, and prepare the process to be in foreground
        or in background.
        """
        foreground_allowed = os.tcgetpgrp(0) == os.getpgrp()
        pid = os.fork()
        os.setpgid(pid, pgid)
        if background == False and foreground_allowed:
            os.tcsetpgrp(sys.stdin.fileno(), os.getpgid(pid))
        return pid

    def child_execution(self, branch, argv, variables):
        if argv[0] in ["jobs", "fg", "cd"]:
            branch.status = self.run_builtin(argv, variables)
            return None
        pid = self.fork_prepare(branch.pgid, branch.background)
        if pid == 0:
            #restore all signals for the child
            tmpsh_signal.reset_signals()
            replace_std_fd(branch.stdin, branch.stdout)
            self.variables_config(variables, only_env=True)
            executable = get_execname(argv[0])
            if executable == None:
                print("Command not found : {}".format(argv[0]))
                exit(127)
            os.execve(executable, argv, gv.ENVIRON)
        else:
            close_fds([branch.stdin, branch.stdout, -1])
            return pid

    def exec_command(self, job_list):
        """
        Use to run a simple command, the branch element which is not
        a SUBSH or a CURSH.
        Prepare command variables, run within the shell if the command is a
        builtin, fork otherwise if it's needed.
        Manage command filedescriptors/pipes.
        """
        variables = self.retrieve_assignation(job_list[-1])
        cmd_args = self.extract_cmd(job_list[-1])
        #Check if the command is only an assignation
        if len(cmd_args) == 0:
            close_fds([job_list[-1].stdin, job_list[-1].stdout, -1])
            if len(variables) >= 1:
                self.variables_config(variables)
                job_list[-1].status = 0
            return
        job_list[-1].pid = self.child_execution(job_list[-1], cmd_args, variables)

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
