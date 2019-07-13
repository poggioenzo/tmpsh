#!/usr/bin/env python3

from utils.tagstokens import TagsTokens as Token
import utils.global_var as gv
import utils.environ as environ
import utils.builtins as builtins
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
        while index < nbr_branch:
            branch = ast.list_branch[index]
            self.replace_variable(branch)
            if self.check_andor(branch) == False:
                index = self.find_newstart(nbr_branch, index, ast)
                continue
            self.perform_subast_replacement(branch)
            branch.pgid = self.check_pgid(ast.list_branch, index)
            self.check_background(ast.list_branch, index)
            #Prepare piping, store stdin pipe for the next command
            if branch.tag_end == "PIPE":
                ast.list_branch[index + 1].stdin, branch.stdout = setup_pipe_fd()
            if self.perform_command_as_subast(branch) == False:
                self.exec_command(branch, pipe_lst)
            self.check_wait_pipe(ast.list_branch, index, pipe_lst)
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
        elif list_branch[index].tag_end == "BACKGROUND_JOBS":
            branch.background = True
            return True
        elif list_branch[index].tag_end == "PIPE":
            branch.background = self.check_background(list_branch, index + 1)
            return branch.background
        return False

    def check_pgid(self, list_branch, index):
        """
        Verify if the current branch have to use the pipeline
        pgid.
        """
        if index > 1 and list_branch[index - 1].tag_end == "PIPE":
            return list_branch[index - 1].pgid
        return 0



    def check_wait_pipe(self, list_branch, index, pipe_lst):
        """
        Check according to the index position in the list_branch if
        some pipe have to be waited.
        """
        if index < 1:
            return 
        #I don't understand how I'm able to wait my pipes.
        #Rewrite condition.
        if not (list_branch[index - 1].tag_end == "PIPE" and \
                list_branch[index].tag_end != "PIPE"):
            return
        for pid in pipe_lst:
            os.waitpid(pid, os.WUNTRACED)
        pipe_lst.clear()


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
                variable = environ.retrieve_variable(token)
                branch.tagstokens.tokens[index] = variable
            elif tag == "SUBAST":
                if branch.subast[index_subast].type == "DQUOTES":
                    self.replace_variable(branch.subast[index_subast].list_branch[0])
                index_subast += 1
            index += 1

    ##################################################################
    ##          Functions to run a branch's subast list             ##
    ##################################################################

    def run_subshell(self, ast, stdin, stdout, background=False, pgid=0):
        """
        From a given ast, run the command in a subshell.
        Redirect stdin and/or stdout if given.
        Wait the subshell and catch his return value if expected.
        """
        #NEED TO WAIT ALL KIND OF SUBSHELL
        settings = termios.tcgetattr(0)
        pid, settings = self.fork_prepare(pgid, background)
        if pid == 0:
            gv.JOBS.clear()
            replace_std_fd(stdin, stdout)
            self.run_ast(ast)
            exit(gv.LAST_STATUS)
        else:
            close_fds([fds.stdin, fds.stdout, -1])
            if method not in ["PIPE", "BACKGROUND_JOBS"]:
                self.analyse_status(pid, "AST")
            os.tcsetpgrp(0, os.getpgrp())
            termios.tcsetattr(sys.stdin.fileno(), termios.TCSADRAIN, settings)
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
                fds = ManagerFD()
                if subast.type == "CMDSUBST2":
                    fds.stdin = pipe_fd[0]
                elif subast.type in ["CMDSUBST1", "CMDSUBST3"]:
                    fds.stdout = pipe_fd[1]
                #NEED TO WAIT SUBSHELL
                subast.pid = self.run_subshell(subast, fds.stdin, fds.stdout)
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
                content = gv.LOCAL_VAR.get(var, "")
            elif subast.type == "DQUOTES":
                self.perform_subast_replacement(subast.list_branch[0])
                content = "".join(subast.list_branch[0].tagstokens.tokens)
            if subast.type in ["BRACEPARAM", "CMDSUBST1","CMDSUBST2","CMDSUBST3","QUOTE", 
                    "DQUOTES"]:
                self.replace_subast(branch, index, content)
            index += 1
        self.replace_ast_tag(branch)

    ##################################################################
    ##     Functions to wait and analyse child + some job control   ##
    ##################################################################

    def analyse_status(self, pid, command, pipe_lst=[]):
        """
        Whenever a child die, behave properly to store information,
        manage background process.
        """
        ### ADD 128 + n when the program is kill by a signal
        pid, return_status = os.waitpid(pid, os.WUNTRACED)

        #Restore shell as the foreground process group
        if os.isatty(sys.stdin.fileno()):
            os.tcsetpgrp(0, os.getpgrp())
        if os.WIFSIGNALED(return_status):
            status = os.WTERMSIG(return_status) + 128
        if os.WIFEXITED(return_status):
            status = os.WEXITSTATUS(return_status)
        if os.WIFSTOPPED(return_status):
            status = os.WSTOPSIG(return_status) + 128
            gv.JOBS.add_job(pid, command, pipe_lst)
        gv.LAST_STATUS = status

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

    def perform_command_as_subast(self, branch):
        """
        If the command is composed of a SUBSH or a CURSH,
        create a layer for this kind of command and run them.
        Save and restore the initial stdin/stdout/stderr to
        prevent change during execution.
        """
        index = 0
        nbr_subast = len(branch.subast)
        while index < nbr_subast:
            subast = branch.subast[index]
            if subast.type in ["SUBSH", "CURSH"]:
                if subast.type == "CURSH" and branch.tag_end not in ["PIPE", "BACKGROUND_JOBS"]:
                    saved_std_fd = self.save_std_fd()
                    replace_std_fd(branch.stdin, branch.stdout)
                    self.run_ast(subast)
                    self.restore_std_fd(saved_std_fd)
                else:
                    pid = self.run_subshell(subast, branch.stdin, branch.stdout, \
                        branch.background, branch.pgid)
                    branch.pid = pid
                    if branch.background:
                        gv.LAST_STATUS = 0
                        gv.JOBS.add_job(pid, branch.command)
                return True
            index += 1
        return False

    def fork_prepare(self, pgid=0, background=True):
        """
        Fork a new process, and prepare the process to be in foreground
        or in background.
        """
        termios_settings = termios.tcgetattr(sys.stdin.fileno())
        pid = os.fork()
        os.setpgid(pid, pgid)
        if background == False and os.isatty(sys.stdin.fileno()):
            os.tcsetpgrp(sys.stdin.fileno(), os.getpgid(pid))
        return pid, termios_settings

    def child_execution(self, branch, argv, variables):
        if argv[0] in ["jobs", "fg", "cd"]:
            return self.run_builtin(argv, variables)
        pid, termios_settings = self.fork_prepare(branch.pgid, branch.background)
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
            print("{} - {}".format(pid, argv[0]))
            close_fds([branch.stdin, branch.stdout, -1])
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
            close_fds([branch.stdin, branch.stdout, -1])
            if len(variables) >= 1:
                self.variables_config(variables)
            return
        branch.pid = self.child_execution(branch, cmd_args, variables)
        if branch.pid == None:
            return
        if branch.background:
            gv.LAST_STATUS = 0
            gv.JOBS.add_job(branch.pid, branch.command)
        elif branch.tag_end != "PIPE":
            self.analyse_status(branch.pid, branch.command)

    def run_builtin(self, cmd_args, variables):
        cmd = "builtins.{}({}, {})".format(cmd_args[0], cmd_args[1:],\
                dict(os.environ))
        gv.LAST_STATUS = exec(cmd)
        return None

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
