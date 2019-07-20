#!/usr/bin/env python3

import os
import enum
import time
import signal
import termios
import sys

import utils.execution.foreground as fg

def dprint(string, *args, **kwargs):
    #Small debug function to print with DEBUG filestream
    print(string, *args, file=DEBUG, **kwargs, flush=True)

class WaitState(enum.Enum):
    FINISH = 0
    RUNNING = 1

##################################################################
##     Functions to wait and analyse child + some job control   ##
##################################################################

def waitpid_layer(pid, mode):
    """
    Use to wait a single pid and analyse his state
    with different waitpid macros.
    """
    pid, return_status = os.waitpid(pid, mode)
    if pid == 0:
        return (0, WaitState.RUNNING)
    if os.WIFSTOPPED(return_status):
        status = os.WSTOPSIG(return_status) + 128
        return (status, WaitState.RUNNING)
    elif os.WIFSIGNALED(return_status):
        status = os.WTERMSIG(return_status) + 128
        return (status, WaitState.FINISH)
    elif os.WIFEXITED(return_status):
        status = os.WEXITSTATUS(return_status)
        return (status, WaitState.FINISH)

def wait_subast(job_branch, mode):
    """
    Wait each subast of the current branch if
    they are CMDSUBST
    """
    nbr_subast = len(job_branch.subast)
    index = 0
    while index < nbr_subast:
        subast = job_branch.subast[index]
        if subast.type in ["CMDSUBST2", "CMDSUBST3"] and subast.complete == False:
            status, state = waitpid_layer(subast.pid, mode)
            if state == WaitState.RUNNING:
                return WaitState.RUNNING
            elif state == WaitState.FINISH:
                subast.complete = True
        index += 1
    return WaitState.FINISH



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
        wait_subast(job, mode)
        status, state = waitpid_layer(job.pid, mode)
        if status == 0 and state == WaitState.RUNNING:
            return state
        job.status = status
        if state == WaitState.RUNNING:
            return WaitState.RUNNING
        job.complete = True
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
        fg.set_foreground(foreground_pgid)
        tcsettings = termios.tcgetattr(0)
        os.kill(-foreground_pgid, signal.SIGCONT)
        if analyse_job_status(job) == WaitState.FINISH:
            self.remove(index)
            print("[{}] + {} continued".format(index, job[-1].pid))
        else:
            print("[{}] + Suspended.".format(index))
        fg.set_foreground(os.getpgrp())
        fg.restore_tcattr()

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

