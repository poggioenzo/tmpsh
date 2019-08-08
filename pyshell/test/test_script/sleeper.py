#!/usr/bin/env python3
import signal
import os
import sys
import time


def handler(signum, *val):
    print("{}: Handle signal {}".format(sys.argv[0], signum))
    signal.signal(signum, signal.SIG_DFL)
    time.sleep(1)
    print("KILLING")
    os.kill(os.getpid(), signum)
    print("out")

if __name__ == "__main__":
    print("Start : {}".format(sys.argv[0]))
    val = signal.signal(signal.SIGTSTP, handler)
    signal.pause()
    print("Done")

