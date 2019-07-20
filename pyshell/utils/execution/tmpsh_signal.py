#!/usr/bin/env python3

import signal
import os
import sys

def interrupt_handler(signum, *args):
    #Wait all foreground process whenever a SIGQUIT is handled
    #by the shell. Called when the shell is also in foreground
    #with other child processes.
    foreground_pgid = os.tcgetpgrp(sys.stdin.fileno())
    pid = -1
    while True and pid != 0:
        try:
            pid, status = os.waitpid(-foreground_pgid, os.WNOHANG)
        except ChildProcessError:
            break
    # How to reproduce this keyboard interrupt with signal in C.
    # Mixing exception and signal is a problem
    raise KeyboardInterrupt

def init_signals():
    signal.signal(signal.SIGINT, interrupt_handler)
    signal.signal(signal.SIGTSTP, signal.SIG_IGN)
    signal.signal(signal.SIGTTIN, signal.SIG_IGN)
    signal.signal(signal.SIGTTOU, signal.SIG_IGN)

def reset_signals():
    signal.signal(signal.SIGINT, signal.SIG_DFL)
    signal.signal(signal.SIGTSTP, signal.SIG_DFL)
    signal.signal(signal.SIGTTIN, signal.SIG_DFL)
    signal.signal(signal.SIGTTOU, signal.SIG_DFL)

