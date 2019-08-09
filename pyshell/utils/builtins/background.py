import utils.global_var as gv
import os
import sys
import signal

def jobs(argv, environ):
    for task in gv.JOBS:
        print("{} : {}".format(task[-1].pid, task[-1].command))

def fg(argv, environ):
    if len(argv) == 0:
        index = 0
    else:
        index = int(argv)
    if index >= len(gv.JOBS.list_jobs):
        print("fg: job not found: {}".format(index), file=sys.stderr)
        return 1
    gv.JOBS.relaunch(index)
    return 0
