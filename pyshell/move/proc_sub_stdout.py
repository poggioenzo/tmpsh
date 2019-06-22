#!/usr/bin/env python3
import sys, os
import fcntl

def prepare_fd(fd):
    """Make a filedescriptor heritable and set O_NONBLOCK flag"""
    os.set_inheritable(fd, True)
    #flag = fcntl.fcntl(fd, fcntl.F_GETFL)
    #fcntl.fcntl(fd, fcntl.F_SETFL, flag | os.O_NONBLOCK)

if __name__ == "__main__":
    pipe = list(os.pipe())
    prepare_fd(pipe[0])
    prepare_fd(pipe[1])
    pid = os.fork()
    if pid == 0:
        executable = os.getcwd() + "/sleeper.py"
        os.dup2(pipe[1], 1)
        os.close(pipe[0])
        os.execve(executable, ["sleeper.py"], os.environ)
    else:
        os.close(pipe[1])
        os.waitpid(pid, 0)

    pid = os.fork()
    if pid == 0:
        executable = os.getcwd() + "/write.py"
        fd = fcntl.fcntl(pipe[0], fcntl.F_DUPFD, 50)
        os.close(pipe[0])
        fd_file = "/dev/fd/" + str(fd)
        os.execve(executable, ["write.py", fd_file], os.environ)
    else:
        #os.write(pipe[1], "shit")
    #    os.close(pipe[1])
        os.waitpid(pid, 0)
