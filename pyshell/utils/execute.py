#!/usr/bin/env python3

from utils.tagstokens import TagsTokens as Token
import utils.global_var as gv
import utils.environ as environ
import fcntl
import sys
import os
import time
import signal


DEBUG = open("/dev/ttys003", "w")
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
        input_pipe = None
        while index < nbr_branch and pid > 0:
            branch = ast.list_branch[index]
            output_pipe = None
            if self.check_andor(branch) == False:
                index = self.find_newstart(nbr_branch, index, ast)
                continue
            #Check if the command have to be launched in background
            if branch.tag_end == "BACKGROUND_JOBS":
                pid = self.run_background_process(branch)
                if pid != 0:
                    index += 1
                    input_pipe = None
                    continue
            if self.perfom_subast_command(branch) == True:
                index += 1
                continue
            self.perform_subast_replacement(branch)
            if branch.tag_end == "PIPE":
                pipes = self.setup_pipe_fd()
                output_pipe = pipes[1]
            self.exec_command(branch, input_pipe, output_pipe)
            if branch.tag_end == "PIPE":
                input_pipe = pipes[0]
            else:
                input_pipe = None
            index += 1
        if pid == 0:
            exit(0)
    
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

    def prepare_substitution_fd(self, type_subst, pipe_fd):
        if type_subst in ["CMDSUBST1", "CMDSUBST3"]:
            os.dup2(pipe_fd[1], sys.stdout.fileno())
        elif type_subst == "CMDSUBST2":
            os.dup2(pipe_fd[0], sys.stdin.fileno())
        os.close(pipe_fd[0])
        os.close(pipe_fd[1])

    def setup_pipe_fd(self):
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

    def run_subshell(self, subast):
        """Run an ast in a subshell/subprocess"""
        if subast.type in ["CMDSUBST1", "CMDSUBST2", "CMDSUBST3"]:
            pipe_fd = self.setup_pipe_fd()
        pid = os.fork()
        if subast.type in ["CMDSUBST1", "CMDSUBST2", "CMDSUBST3"] and pid == 0:
            self.prepare_substitution_fd(subast.type, pipe_fd)
        if pid == 0:
            self.run_ast(subast)
            exit(gv.LAST_STATUS)
        else:
            if subast.type in ["CMDSUBST1", "CMDSUBST3"]:
                subast.link_fd = pipe_fd[0]
                os.close(pipe_fd[1])
            elif subast.type == "CMDSUBST2":
                subast.link_fd = pipe_fd[1]
                os.close(pipe_fd[0])
            elif subast.type == "SUBSH":
                self.analyse_status(pid)

    def perfom_subast_command(self, branch):
        """Run each subast which are other shell commands."""
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
                        ["QUOTE", "CMDSUBST1", "CMDSUBST2", "CMDSUBST3", "BRACEPARAM"]:
                    branch.tagstokens.tags[index] = "STMT"
                pos_subast += 1
            index += 1

    def perform_subast_replacement(self, branch):
        """
        Inside a branch, replace each subast element by the generated content
        or the cmdsubst /dev/fd file.
        """
        index = 0
        nbr_ast = len(branch.subast)
        while index < nbr_ast:
            subast = branch.subast[index]
            if subast.type == "QUOTE":
                content = "".join(subast.list_branch[0].tagstokens.tokens)
            elif subast.type == "CMDSUBST1":
                content = os.read(subast.link_fd, 800000).decode()
            elif subast.type in ["CMDSUBST2", "CMDSUBST3"]:
                content = "/dev/fd/" + str(subast.link_fd)
            elif subast.type == "BRACEPARAM":
                var = subast.list_branch[0].tagstokens.tokens[0]
                content = gv.LOCAL_VAR.get(var, "")
            if subast.type in ["BRACEPARAM", "CMDSUBST1","CMDSUBST2","CMDSUBST3","QUOTE"]:
                self.replace_subast(branch, index, content)
            index += 1
        self.replace_ast_tag(branch)

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

    def close_branch_fd(self, branch):
        """Close extra pipe fd of CMDSUBST or PIPE subast"""
        index = 0
        nbr_subast = len(branch.subast)
        while index < nbr_subast:
            ast = branch.subast[index]
            if ast.type in ["CMDSUBST1", "CMDSUBST2", "CMDSUBST3"]:
                os.close(ast.link_fd)
            index += 1

    def exec_command(self, branch, input_pipe, output_pipe):
        """Fork + execve a given list of argument"""
        #Check if the command is only an assignation
        variables = self.retrieve_assignation(branch)
        cmd_args = self.extract_cmd(branch)
        if len(cmd_args) == 0:
            if len(variables) == 1:
                os.close(input_pipe) if input_pipe else None
                os.close(output_pipe) if output_pipe else None
                self.environ_configuration(variables)
            return
        pid = os.fork()
        if pid == 0:
            #run the child
            if input_pipe != None:
                os.dup2(input_pipe, sys.stdin.fileno())
                os.close(input_pipe)
            if output_pipe != None:
                os.dup2(output_pipe, sys.stdout.fileno())
                os.close(output_pipe)
            self.environ_configuration(variables, only_env=True)
            executable = get_execname(cmd_args[0])
            if executable == None:
                print("Command not found : {}".format(cmd_args[0]))
                exit(127)
            os.execve(executable, cmd_args, os.environ)
        else:
            #Get status from the father
            if input_pipe:
                os.close(input_pipe)
            if output_pipe:
                os.close(output_pipe)
            self.close_branch_fd(branch)
            if branch.tag_end != "PIPE":
                self.analyse_status(pid)

    def prepare_stmt(self, branch):
        """
        For each STMT token, tansform variable values.
        If a STMT is following an other STMT, concat them in a single token.
        """
        index = 0
        tagstok = branch.tagstokens
        while index < tagstok.length:
            if tagstok.tags[index] == "STMT":
                stmt_str = tagstok.tokens[index]
                #Replace variable
                if stmt_str[0] == "$":
                    variable_value = environ.retrieve_variable(stmt_str)
                    tagstok.tokens[index] = variable_value
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
        self.prepare_stmt(branch)
        command = []
        for index in range(branch.tagstokens.length):
            if branch.tagstokens.tags[index] in gv.GRAMMAR.grammar["STMT"]:
                command.append(branch.tagstokens.tokens[index])
        return command
