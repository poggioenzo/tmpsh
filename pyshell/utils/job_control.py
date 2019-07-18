#!/usr/bin/env python3

import os
import enum
import time
import signal
import termios
import sys

class WaitState(enum.Enum):
    FINISH = 0
    RUNNING = 1

##################################################################
##     Functions to wait and analyse child + some job control   ##
##################################################################

def analyse_job_status(job_list, mode=os.WUNTRACED):
    """
    Whenever a child die, behave properly to store information,
    manage background process.
    """
    index = len(job_list) - 1
    while index >= 0:
        job = job_list[index]
        if job.complete or job.pid is None:
            index -= 1
            continue
        debug = open("/dev/ttys003", "w")
        print("start", file=debug)
        pid, return_status = os.waitpid(job.pid, mode)
        print("end", file=debug)
        debug.close()
        #Leave the loop if no pid is get, os.WNOHANG activate
        if pid == 0:
            return WaitState.RUNNING
        if os.WIFSIGNALED(return_status):
            job.status = os.WTERMSIG(return_status) + 128
            job.complete = True
        if os.WIFEXITED(return_status):
            job.complete = True
            job.status = os.WEXITSTATUS(return_status)
        if os.WIFSTOPPED(return_status):
            job.status = os.WSTOPSIG(return_status) + 128
            return WaitState.RUNNING
        index -= 1
    return WaitState.FINISH

class BackgroundJobs:
    def __init__(self):
        self.list_jobs = []
        self.allow_background = True

    def add_job(self, new_job):
        """Add a new process in the background process group"""
        self.list_jobs.append(new_job.copy())
        print("[{}] {}".format(len(self.list_jobs), new_job[-1].pid))
        self.fix_pgid(self.list_jobs[-1])

    def fix_pgid(self, job):
        """
        Set up the pgid attribute in each branch on the job.
        """
        index = 0
        nbr_job = len(job)
        pgid_ref = 0
        while index < nbr_job and pgid_ref == 0:
            if job[index].pgid != 0:
                pgid_ref = job[index].pgid
            if job[index].pid != None:
                pgid_ref = os.getpgid(job[index].pid)
            index += 1
        if pgid_ref == 0:
            return
        index = 0
        while index < nbr_job:
            job[index].pgid = pgid_ref
            index += 1

    def __iter__(self):
        self._index = 0
        return iter(self.list_jobs)

    def __next__(self):
        jobs = self.list_jobs[self._index]
        self._index += 1
        return jobs

    def __str__(self):
        return str(self.list_jobs)

    def get_index_pid(self, index):
        """
        Return the jobs pid at the given index.
        """
        return self.list_jobs[index].pid

    def is_running(self, index):
        """
        Check if any process in the job is still running or if it's 
        already finish.
        """
        job = self.list_jobs[index]
        return analyse_job_status(job, mode=os.WNOHANG)

    def remove(self, index):
        self.list_jobs.pop(index)

    def clear(self):
        self.list_jobs.clear()

    def relaunch(self, index):
        """
        Push a job in foreground and send him SIGCONT.
        Keep it in the background job list if it's suspended.
        """
        if self.is_running(index) == WaitState.FINISH:
            print("tmpsh: fg: job has terminated")
            self.remove(index)
            return
        job = self.list_jobs[index]
        foreground_pgid = job[-1].pgid
        os.tcsetpgrp(sys.stdin.fileno(), foreground_pgid)
        tcsettings = termios.tcgetattr(0)
        os.kill(-foreground_pgid, signal.SIGCONT)
        if analyse_job_status(job) == WaitState.FINISH:
            self.remove(index)
            print("[{}] + {} continued", index, job[-1].pid)
        else:
            print("[{}] + Suspended.".format(index))
        termios.tcsetattr(sys.stdin.fileno(), termios.TCSADRAIN, tcsettings)
        os.tcsetpgrp(0, os.getpgrp())

    def wait_zombie(self):
        """
        Called before giving back the prompt to the user.
        Check if some jobs are done and remove them from the current joblist.
        """
        index = 0
        nbr_job = len(self.list_jobs)
        index_to_del = []
        #Check which jobs is over by waiting all of them
        #Add all of those who need to be removed in index_to_del list.
        while index < nbr_job:
            if self.is_running(index) == WaitState.FINISH:
                job = self.list_jobs[index]
                index_to_del.append(index)
                print("[{}] + Done {}".format(index, job[-1].command))
            index += 1

        #Finally, remove from our joblist those which are over.
        index = 0
        nbr_deletion = len(index_to_del)
        while index < nbr_deletion:
            deletion_index = index_to_del[index]
            del self.list_jobs[deletion_index - index]
            index += 1

