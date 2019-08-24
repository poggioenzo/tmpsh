import utils.global_var as gv
import os
import sys
import signal

def is_job_id(argument_name):
    return argument_name[0] == "%" and argument_name[1:].isdigit() 


def diplay_job(job, index, p_flag, l_flag):
    status = "Running" if job[0].running else "Stopped"
    #print only PGID of the job.
    if p_flag:
        print(job[-1].pgid)
    elif l_flag:
        pgid = job[-1].pgid
        print("[{}] - {} {}     {}".format(index, pgid, status, job[-1].command))
    else:
        print("[{}] - {}  {}".format(index, status, job[-1].command))



def jobs(argv, environ):
    argc = len(argv)
    l_flag = False
    p_flag = False
    if argc >= 1 and argv[0] == "-p":
        p_flag = True
        argv.pop(0)
    elif argc >= 1 and argv[0] == "-l":
        l_flag = True
        argv.pop(0)
    if len(argv) > 0:
        for argument in argv:
            if is_job_id(argument):
                index = int(argument[1:])
                job = gv.JOBS.get_job(index)
                if job == None:
                    print("jobs: No such job '{}'".format(argument), file=sys.stderr)
                    return 1
                else:
                    diplay_job(job, index, p_flag, l_flag)
            else:
                print("jobs: No such job '{}'".format(argument))
                return 1

    else:
        for index, task in enumerate(gv.JOBS):
            diplay_job(task, index, p_flag, l_flag)
    return 0

def fg(argv, environ):
    if len(argv) == 0:
        argv = ["%0"]
    for argument in argv:
        if is_job_id(argument):
            index = int(argument[1:])
            if gv.JOBS.get_job(index) is None:
                print("jobs: No such job '{}'".format(argument), file=sys.stderr)
                return 1
            else:
                gv.JOBS.relaunch(index)
    return 0
