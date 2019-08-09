import os
import sys
import fcntl

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

def close_fds(fd_list):
    """
    Close all fds in the given list. The list must end with -1.
    """
    index = 0
    while fd_list[index] != -1:
        if fd_list[index] is not None:
            os.close(fd_list[index])
        index += 1
        

#Save_std_fd and restore_std_fd can be combinated in a single function
#in C with a static variable to store saved stdin/stdout/stderr

def save_std_fd():
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

def restore_std_fd(std_fds):
    """
    From saved stdin/stdout/stderr of self.saved_std_fd, restore the
    each fds.
    """
    replace_fd(std_fds[0], sys.stdin.fileno())
    replace_fd(std_fds[1], sys.stdout.fileno())
    replace_fd(std_fds[2], sys.stderr.fileno())

