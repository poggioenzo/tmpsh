#!/usr/bin/env python3
import signal
import os
import sys


def handler(signum):
    print("Handle signal {}".format(signal.getsignal(signum)))
    signal.signal(signum, signal.SIG_DFL)
    time.sleep(1)
    print("KILLING")
    os.kill(os.getpid(), signum)

if __name__ == "__main__":
    fd = open("/dev/pts/7", "w")
    print("Start : {}".format(sys.argv[0]), file=fd)
    signal.signal(signal.SIGTSTP, handler)
    signal.sigwait([signal.SIGTSTP])

