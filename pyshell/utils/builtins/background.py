import utils.global_var as gv
import os
import sys
import signal

def jobs(argv, environ):
    for task in gv.JOBS:
        pid = task[0]
        command = task[1]
        print("{} : {}".format(pid, command))

def fg(argv, environ):
    if len(argv) == 0:
        index = 0
    else:
        index = int(argv)
    if index > len(gv.JOBS.list_jobs):
        print("fg: job not found: {}".format(index), file=sys.stderr)
        return 1
    #Check if the jobs is terminated
    expected_jobs_pid = gv.JOBS.get_index_pid(index)
    pid, status = os.waitpid(expected_jobs_pid, os.WNOHANG)
    if pid != 0:
        print("tmpsh: fg: job has terminated.")
        return
    os.tcsetpgrp(0, expected_jobs_pid)
    os.kill(expected_jobs_pid, signal.SIGCONT)
    pid, status = os.waitpid(expected_jobs_pid, 0)
    gv.JOBS.remove(index)

    return 0



