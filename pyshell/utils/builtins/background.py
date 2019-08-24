import utils.global_var as gv
import os
import sys
import signal

def is_job_id(argument_name):
    return argument_name[0] == "%" and argument_name[1:].isdigit() 


def diplay_job(job, p_flag, l_flag):
    status = "Running" if job.branches[0].running else "Stopped"
    #print only PGID of the job.
    if p_flag:
        print(job.pgid)
    elif l_flag:
        pgid = job.pgid
        print("[{}] - {} {}     {}".format(job.number, pgid, status, job.command))
    else:
        print("[{}] - {}  {}".format(job.number, status, job.command))



def jobs(argv, environ):
    argc = len(argv)
    p_flag = l_flag = False
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
                    diplay_job(job, p_flag, l_flag)
            else:
                print("jobs: No such job '{}'".format(argument))
                return 1
    else:
        for index, job in enumerate(gv.JOBS.list_jobs):
            diplay_job(job, p_flag, l_flag)
    return 0

def get_default_job(caller, argv):
    if len(argv) == 0:
        if len(gv.JOBS.list_jobs) == 0:
            print(caller + ": no current job", file=sys.stderr)
            return False
        argv.append("%" + str(gv.JOBS.list_jobs[0].number))
    return True

def fg(argv, environ):
    if get_default_job("fg", argv) == False:
        return 1
    for argument in argv:
        if is_job_id(argument):
            index = int(argument[1:])
            if gv.JOBS.get_job(index) is None:
                print("fg: No such job '{}'".format(argument), file=sys.stderr)
                return 1
            gv.JOBS.relaunch(index)
    return 0

def bg(argv, environ):
    if get_default_job("bg", argv) == False:
        return 1
    for argument in argv:
        if is_job_id(argument):
            index = int(argument[1:])
            job = gv.JOBS.get_job(index)
            if job is None:
                print("bg: No such job '{}'".format(argument), file=sys.stderr)
                return 1
            if job.branches[0].running == False:
                job.branches[0].running = True
                os.kill(-job.pgid, signal.SIGCONT)
                print("[{}] {}".format(job.number, job.command))
    return 0 

