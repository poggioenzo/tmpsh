#!/usr/bin/env python3

from utils.tagstokens import TagsTokens as Token
import utils.global_var as gv
import utils.environ as environ
import utils.builtins.background as builtin
import fcntl
import sys
import os
import time
import signal


DEBUG = open("/dev/pts/4", "w")
def dprint(string, *args, **kwargs):
    print(string, *args, file=DEBUG, **kwargs)

TheFork = os.fork

def forker():
    start = time.clock()
    pid = TheFork()
    end = time.clock() - start
    if pid != 0:
        dprint("FORK")
    return pid

#os.fork = forker

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

class ManagerFD:
    def __init__(self):
        self.stdin = None
        self.stdout = None
        self.saved_input_pipe = None
        self.redirection_list = None

    def manage_pipe_fd(self, ast, index):
        self.stdout = None
        if index > 0 and ast.list_branch[index - 1].tag_end == "PIPE":
            self.stdin = self.saved_input_pipe
        else:
            self.stdin = None
        self.saved_input_pipe = None
    pass

class Executor:
    """From an AST, run each command"""
    def __init__(self, ast):
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
        pid = os.getpid()
        fds = ManagerFD()
        while index < nbr_branch and pid > 0:
            branch = ast.list_branch[index]
            self.replace_variable(branch)
            fds.manage_pipe_fd(ast, index)
            if self.check_andor(branch) == False:
                index = self.find_newstart(nbr_branch, index, ast)
                continue
            #Check if the command have to be launched in background
            if branch.tag_end == "BACKGROUND_JOBS":
                pid = self.run_background_process(branch)
                if pid != 0:
                    index += 1
                    continue
            self.perform_subast_replacement(branch)
            #Prepare piping, store stdin pipe for the next command
            if branch.tag_end == "PIPE":
                fds.saved_input_pipe, fds.stdout = setup_pipe_fd()
            if self.perfom_command_as_subast(branch, fds) == False:
                self.exec_command(branch, fds.stdin, fds.stdout)
            index += 1
        #Exit background process
        if pid == 0:
            exit(0)
        gv.JOBS.wait_zombie()
    
    ##################################################################
    ##                  Utils for self.run_ast                      ##
    ##################################################################

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

    def run_background_process(self, branch):
        """Prepare the current command to be run in background"""
        pid = os.fork()
        if pid > 0:
            command = "".join(branch.tagstokens.tokens)
            gv.JOBS.add_job(pid, command)
            gv.LAST_STATUS = 0
        else:
            os.setpgid(0, 0)
        return pid

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

    def run_subshell(self, ast, fds, wait=False):
        """
        From a given ast, run the command in a subshell.
        Redirect stdin and/or stdout if given.
        Wait the subshell and catch his return value if expected.
        """
        pid = os.fork()
        if pid == 0:
            if fds.stdin:
                replace_fd(fds.stdin, sys.stdin.fileno())
            if fds.stdout:
                replace_fd(fds.stdout, sys.stdout.fileno())
            self.run_ast(ast)
            exit(gv.LAST_STATUS)
        else:
            if fds.stdin:
                os.close(fds.stdin)
            if fds.stdout:
                os.close(fds.stdout)
            if wait:
                self.analyse_status(pid)
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
                self.run_subshell(subast, fds)
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
                content = os.read(subast.link_fd, 800000).decode()
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

    def analyse_status(self, pid):
        """
        Whenever a child die, behave properly to store information,
        manage background process.
        """
        ### ADD 128 + n when the program is kill by a signal
        pid, return_status = os.waitpid(pid, 0)
        status = os.WEXITSTATUS(return_status)
        gv.LAST_STATUS = status
        if os.WIFSTOPPED(return_status):
            #Set job in background
            pass

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

    def environ_configuration(self, variables, only_env=False):
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

    def perfom_command_as_subast(self, branch, fds):
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
                saved_std_fd = self.save_std_fd()
                wait = False if fds.stdout != None else True
                if subast.type == "CURSH" and wait == True:
                    if fds.stdin:
                        replace_fd(fds.stdin, sys.stdin.fileno())
                    self.run_ast(subast)
                else:
                    self.run_subshell(subast, fds, wait)
                self.restore_std_fd(saved_std_fd)
                return True
            index += 1
        return False

    def exec_command(self, branch, stdin, stdout):
        """Fork + execve a given list of argument"""
        variables = self.retrieve_assignation(branch)
        cmd_args = self.extract_cmd(branch)
        #Check if the command is only an assignation
        if len(cmd_args) == 0:
            if len(variables) == 1:
                os.close(stdin) if stdin else None
                os.close(stdout) if stdout else None
                self.environ_configuration(variables)
            return
        if branch.tag_end == "BACKGROUND_JOBS":
            pid = 0
        else:
            pid = os.fork()
        if pid == 0:
            #run the child
            if stdin != None:
                replace_fd(stdin, sys.stdin.fileno())
            if stdout != None:
                replace_fd(stdout, sys.stdout.fileno())
            self.environ_configuration(variables, only_env=True)
            if cmd_args[0] in ["jobs", "fg"]:
                return self.run_builtin(cmd_args)
            executable = get_execname(cmd_args[0])
            if executable == None:
                print("Command not found : {}".format(cmd_args[0]))
                exit(127)
            os.execve(executable, cmd_args, os.environ)
        else:
            #Get status from the father
            os.close(stdin) if stdin else None
            os.close(stdout) if stdout else None
            if branch.tag_end != "PIPE":
                self.analyse_status(pid)

    def run_builtin(self, cmd_args):
        cmd = "builtin.{}({}, {})".format(cmd_args[0], cmd_args[1:],\
                dict(os.environ))
        exec(cmd)
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
