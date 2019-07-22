#!/usr/bin/env python3

import os
import sys

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
        #print(f"tmpsh: No such file or directory : {cmd}", file=sys.stderr)
        print("tmpsh: No such file or directory : {}".format(cmd), file=sys.stderr)
        return None
    if os.access(cmd, os.X_OK) == False:
        print("zsh: permission denied: {}".format(cmd), file=sys.stderr)
        return None
    return cmd

def get_execname(cmd):
    """
    From a given STMT, verify if the given file correspond to a file,
    or if it's a command to search in PATH.
    Check if the given command can be run, display the appropriate
    error message otherwise.
    """
    cmd = cmd.strip() # ! Get space in STMT with PIPE
    if "/" in cmd:
        return check_rights(cmd)
    exec_folders = os.environ["PATH"]
    for folder in exec_folders.split(":"):
        execname = os.path.join(folder, cmd)
        if os.path.isfile(execname):
            return check_rights(execname)
    print("tmpsh: command not found: {}".format(cmd), file=sys.stderr)
    return None
