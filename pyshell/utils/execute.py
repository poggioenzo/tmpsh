#!/usr/bin/env python3

from utils.tagstokens import TagsTokens as Token
import utils.global_var as gv
import os

def get_execname(cmd):
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
        tagstok = ast.list_branch[0].tagstokens
        cmd = self.extract_cmd(ast.list_branch[0])
        self.exec_command(cmd)

    def exec_command(self, cmd_args):
        """Fork + execve a given list of argument"""
        pid = os.fork()
        if pid == 0:
            executable = get_execname(cmd_args[0])
            os.execve(executable, cmd_args, os.environ)
            pass
        else:
            status = os.waitpid(pid, 0)


    def extract_cmd(self, branch):
        """Get only token used to run a command, format argv + environ"""
        command = []
        for index in range(branch.tagstokens.length):
            if branch.tagstokens.tags[index] in gv.GRAMMAR.grammar["STMT"]:
                command.append(branch.tagstokens.tokens[index])
        return command

