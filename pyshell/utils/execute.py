#!/usr/bin/env python3

from utils.tagstokens import TagsTokens as Token
import utils.global_var as gv
import fcntl
import sys
import os

def get_execname(cmd):
    exec_folders = os.environ["PATH"]
    for folder in exec_folders.split(":"):
        execname = os.path.join(folder, cmd)
        if os.path.isfile(execname):
            return execname
    print("no exec")
    return None


class Executor:
    """From an AST, run each command"""
    def __init__(self, ast):
        self.ast = ast
        self.run_ast()

    def run_ast(self, ast=None):
        if ast == None:
            ast = self.ast
        index = 0
        nbr_branch = len(ast.list_branch)
        pid = os.getpid()
        while index < nbr_branch and pid > 0:
            branch = ast.list_branch[index]
            if self.check_andor(branch) == False:
                index = self.find_newstart(nbr_branch, index, ast)
                continue
            #Check if the command have to be launched in background
            if branch.tag_end == "BACKGROUND_JOBS":
                pid = self.run_background_process(branch)
                if pid != 0:
                    index += 1
                    continue
            if self.perfom_subast_command(branch) == True:
                index += 1
                continue
            self.perform_subast_replacement(branch)
            cmd = self.extract_cmd(branch)
            self.exec_command(cmd)
            index += 1
        if pid == 0:
            exit(0)

    def run_background_process(self, branch):
        """Prepare the current command to be run in background"""
        pid = os.fork()
        if pid > 0:
            command = "".join(branch.tagstokens.tokens)
            gv.JOBS.add_job(pid, command)
        else:
            os.setpgid(0, 0)
        return pid

    def prepare_substitution_pre_fork(self, type_subst):
        """
        When a CMDSUBST is done, prepare his fd according to the expected
        configuration.
        """
        read_fd, write_fd = os.pipe()

    def prepare_substitution_fd(self, type_subst, pipe_fd):
        if type_subst == "CMDSUBST1":
            os.dup2(pipe_fd[1], sys.stdout.fileno())
        elif type_subst == "CMDSUBST2":
            os.dup2(pipe_fd[0], sys.stdin.fileno())
        elif type_subst == "CMDSUBST3":
            os.dup2(pipe_fd[1], sys.stdout.fileno())

    def configure_pipe_fd(self, pipe_fd, non_blocking=False):
        """"""
        #Change fd value to get fd in range of [63:infinite[
        old_pipe = pipe_fd.copy()
        pipe_fd[0] = fcntl.fcntl(pipe_fd[0], fcntl.F_DUPFD, 63)
        pipe_fd[1] = fcntl.fcntl(pipe_fd[1], fcntl.F_DUPFD, 63)
        os.set_inheritable(pipe_fd[0], True)
        os.set_inheritable(pipe_fd[1], True)
        os.close(old_pipe[0])
        os.close(old_pipe[1])
        if non_blocking:
            opts = fcntl.fcntl(pipe_fd[0], fcntl.F_GETFL)
            fcntl.fcntl(pipe_fd[0], fcntl.F_SETFL, opts | os.O_NONBLOCK)
            opts = fcntl.fcntl(pipe_fd[1], fcntl.F_GETFL)
            fcntl.fcntl(pipe_fd[1], fcntl.F_SETFL, opts | os.O_NONBLOCK)

    def run_subshell(self, subast):
        """Run an ast in a subshell"""
        if subast.type in ["CMDSUBST1", "CMDSUBST2", "CMDSUBST3"]:
            pipe_fd = list(os.pipe())
            non_blocking = subast.type == "CMDSUBST1"
            self.configure_pipe_fd(pipe_fd, non_blocking=non_blocking)
        pid = os.fork()
        if subast.type in ["CMDSUBST1", "CMDSUBST2", "CMDSUBST3"] and pid == 0:
            self.prepare_substitution_fd(subast.type, pipe_fd)
        if pid == 0:
            self.run_ast(subast)
            exit(gv.LAST_STATUS)
        else:
            if subast.type in ["CMDSUBST1", "SUBSH", "CMDSUBST3"]:
                self.analyse_status(pid)

    def perfom_subast_command(self, branch):
        """Run each command of subast which are not variable replacement"""
        index = 0
        nbr_subast = len(branch.subast)
        runned = False
        while index < nbr_subast:
            subast = branch.subast[index]
            if subast.type in ["SUBSH", "CMDSUBST1", "CMDSUBST2", "CMDSUBST3"]:
                self.run_subshell(subast)
            if subast.type == "CURSH":
                self.run_ast(subast)
            if subast.type in ["CURSH", "SUBSH"]:
                runned = True
            index += 1
        return runned


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

    def perform_subast_replacement(self, branch):
        """Inside a branch, replace each subast element"""
        index = 0
        nbr_ast = len(branch.subast)
        while index < nbr_ast:
            subast = branch.subast[index]
            if subast.type == "QUOTE":
                content = "".join(subast.list_branch[0].tagstokens.tokens)
                self.replace_subast(branch, index, content)
            index += 1
        pass

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

    def analyse_status(self, pid):
        """
        Whenever a child die, behave properly to store information,
        manage background process.
        """
        pid, return_status = os.waitpid(pid, 0)
        status = os.WEXITSTATUS(return_status)
        gv.LAST_STATUS = status
        if os.WIFSTOPPED(return_status):
            #Set job in background
            pass

    def exec_command(self, cmd_args):
        """Fork + execve a given list of argument"""
        if (len(cmd_args) == 0):
            return
        pid = os.fork()
        if pid == 0:
            #run the child
            executable = get_execname(cmd_args[0])
            os.execve(executable, cmd_args, os.environ)
        else:
            #Get status from the father
            self.analyse_status(pid)

    def extract_cmd(self, branch):
        """Get only token used to run a command, format argv + environ"""
        command = []
        for index in range(branch.tagstokens.length):
            if branch.tagstokens.tags[index] in gv.GRAMMAR.grammar["STMT"]:
                command.append(branch.tagstokens.tokens[index])
        return command
