#!/usr/bin/env python3
import sys, os
import fcntl

def prepare_fd(fd):
    """Make a filedescriptor heritable and set O_NONBLOCK flag"""
    os.set_inheritable(fd, True)
    #flag = fcntl.fcntl(fd, fcntl.F_GETFL)
    #fcntl.fcntl(fd, fcntl.F_SETFL, flag | os.O_NONBLOCK)

if __name__ == "__main__":
    pipe = os.pipe()
    prepare_fd(pipe[0])
    prepare_fd(pipe[1])
    pid = os.fork()
    if pid == 0:
        executable = os.getcwd() + "/file_read.py"
        os.dup2(pipe[0], 0)
        os.close(pipe[1])
        os.execve(executable, ["file_read.py"], os.environ)
    else:
        os.close(pipe[0])
    pid = os.fork()
    if pid == 0:
        executable = os.getcwd() + "/file_write.py"
        fd_file = "/dev/fd/" + str(pipe[1])
        os.execve(executable, ["write.py", fd_file], os.environ)
    else:
        #os.write(pipe[1], "shit")
        os.close(pipe[1])
        os.waitpid(pid, 0)
        import time
        time.sleep(10)
