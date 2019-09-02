#!/usr/bin/env python3

import os
import sys
from utils.builtins.hash import HashExec
import utils.global_var as gv

def read_fd(fd):
    """
    Read the entire content from a given filedescriptor.
    """
    BUFFER = 150
    text = ''
    while True:
        content = os.read(fd, BUFFER).decode()
        if content == "":
            break
        text += content
    return text

def check_rights(cmd):
    """
    When the shell research exepected executable, check
    if it's possible to run the given file.
    Check permission + file existence.
    """
    if os.access(cmd, os.F_OK) == False:
        print("tmpsh: No such file or directory : {}".format(cmd), file=sys.stderr)
        return None
    if os.access(cmd, os.X_OK) is False or os.access(cmd, os.R_OK) is False:
        print("tmpsh: permission denied: {}".format(cmd), file=sys.stderr)
        return None
    return cmd

def get_execname(cmd):
    """
    From a given STMT, verify if the given file correspond to a file,
    or if it's a command to search in PATH.
    Check if the given command can be run, display the appropriate
    error message otherwise.
    """
    if cmd in gv.HASH:
        gv.HASH[cmd].count += 1
        return check_rights(gv.HASH[cmd].exec_file)
    if cmd in ["jobs", "fg", "bg", "cd", "umask", "exit", "hash"]:
        return cmd
    if "/" in cmd:
        return check_rights(cmd)
    exec_folders = os.environ["PATH"]
    for folder in exec_folders.split(":"):
        execname = os.path.join(folder, cmd)
        if os.path.isfile(execname):
            gv.HASH[cmd] = HashExec(execname)
            gv.HASH[cmd].count += 1
            return check_rights(execname)
    print("tmpsh: command not found: {}".format(cmd), file=sys.stderr)
    return None
