import utils.execution.variables as variables_mod
import utils.execution.fd_management as fd
import utils.global_var as gv
import utils.execution.tmpsh_signal as tmpsh_signal
import utils.builtins as builtins
import utils.execution.redirection as redirection
import utils.execution.file as file
import utils.execution.forker as forker

import os

def join_stmt(branch):
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

def extract_cmd(branch):
    """Get only token used to run a command, format argv + environ"""
    join_stmt(branch)
    command = []
    for index in range(branch.tagstokens.length):
        if branch.tagstokens.tags[index] == "STMT":
            command.append(branch.tagstokens.tokens[index])
    return command

def run_builtin(cmd_args, variables):
    """
    Run builtin commands from the builtin module.
    Format the python command to execute and execute it.
    Save, modify and restore the global environnement if needed.
    """
    save_environ = len(variables) > 0
    if save_environ:
        save_environ = gv.ENVIRON.copy()
        variables_mod.variables_config(variables, only_env=True)
    cmd = "builtins.{}({}, {})".format(cmd_args[0], cmd_args[1:],\
            dict(os.environ))
    status = exec(cmd)
    if save_environ:
        gv.ENVIRON = save_environ
    return status

def child_execution(branch, argv, variables):
    """
    Run a builtin, or fork + execve a given executable.
    Setup redirection and change stdin/stdout as needed by any kind of pipe.
    Setup list of variables as environnement variables.
    """
    if argv[0] in ["jobs", "fg", "cd", "umask", "exit"]:
        branch.status = run_builtin(argv, variables)
        return None
    pid = forker.fork_prepare(branch.pgid, branch.background)
    if pid == 0:
        #restore all signals for the child
        tmpsh_signal.reset_signals()
        fd.replace_std_fd(branch.stdin, branch.stdout)
        redirection.setup_redirection(branch)
        variables_mod.variables_config(variables, only_env=True)
        executable = file.get_execname(argv[0])
        if executable == None:
            exit(127)
        os.execve(executable, argv, gv.ENVIRON)
    else:
        fd.close_fds([branch.stdin, branch.stdout, -1])
        branch.running = True
        return pid

def exec_command(branch):
    """
    Use to run a simple command, the branch element which is not
    a SUBSH or a CURSH.
    Prepare command variables, run within the shell if the command is a
    builtin, fork otherwise if it's needed.
    Manage command filedescriptors/pipes.
    """
    variables = variables_mod.retrieve_assignation(branch)
    cmd_args = extract_cmd(branch)
    #Check if the command is only an assignation
    if len(cmd_args) == 0:
        fd.close_fds([branch.stdin, branch.stdout, -1])
        if len(variables) >= 1:
            variables_mod.variables_config(variables)
            branch.status = 0
        return
    branch.pid = child_execution(branch, cmd_args, variables)

