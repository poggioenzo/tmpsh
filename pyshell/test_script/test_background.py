#!/usr/bin/env python3

import os, time, signal
import sys


def init_shell():
    signal.signal(signal.SIGINT, signal.SIG_IGN)
    signal.signal(signal.SIGQUIT, signal.SIG_IGN)
    signal.signal(signal.SIGTSTP, signal.SIG_IGN)
    signal.signal(signal.SIGTTIN, signal.SIG_IGN)
    signal.signal(signal.SIGTTOU, signal.SIG_IGN)
    signal.signal(signal.SIGCHLD, signal.SIG_IGN)


def run_child():

    execname = sys.argv[1]
    args_exec = sys.argv[1:]

    signal.signal(signal.SIGINT, signal.SIG_DFL);
    signal.signal(signal.SIGQUIT, signal.SIG_DFL);
    signal.signal(signal.SIGTSTP, signal.SIG_DFL);
    signal.signal(signal.SIGTTIN, signal.SIG_DFL);
    signal.signal(signal.SIGTTOU, signal.SIG_DFL);
    signal.signal(signal.SIGCHLD, signal.SIG_DFL);
    os.setpgid(0, 0)
    os.tcsetpgrp(0, os.getpgrp())
    os.execve(execname, args_exec, os.environ)


def error(msg):
    print(msg, file=sys.stderr)
    exit(1)

def read_line():
    print(os.read(0, 250).decode(), end='')



def main():
    pid = os.fork()
    if pid == 0:
        run_child()#args
    else:
        os.setpgid(pid, 0)
        os.tcsetpgrp(0, pid)
        print("Father starting wait.")
        status = os.waitpid(pid, os.WUNTRACED)
        print("Father end wait.")
        os.tcsetpgrp(0, os.getpgrp())
        if os.WIFSTOPPED(status[1]):
            wait_time = 2
            print("Relaunch if {} seconds.".format(wait_time))
            time.sleep(wait_time)
            os.tcsetpgrp(0, pid)
            os.kill(pid, signal.SIGCONT)
            status = os.waitpid(pid, os.WUNTRACED)
            os.tcsetpgrp(0, os.getpgrp())
            print("End Father.")
            exit(1)
        read_line()
        term_sig = os.WSTOPSIG(status[1])
        if (term_sig == signal.SIGTSTP):
            print("Yolo")

    pass

if __name__ == "__main__":
    if len(sys.argv) == 1:
        error("No args.")
    init_shell()
    main()
