#!/usr/bin/env python3

import os
import enum
import time
import signal
import termios
import sys

import utils.execution.foreground as fg


def dprint(string, *args, **kwargs):
    # Small debug function to print with DEBUG filestream
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


def analyse_job_status(job_branches, mode=os.WUNTRACED):
    """
    Whenever a child die, behave properly to store information,
    manage background process.
    """
    index = len(job_branches) - 1
    while index >= 0:
        branch = job_branches[index]
        if branch.complete or branch.pid is None:
            index -= 1
            continue
        wait_subast(branch, mode)
        status, state = waitpid_layer(branch.pid, mode)
        if status == 0 and state == WaitState.RUNNING:
            return state
        branch.status = status
        if state == WaitState.RUNNING:
            branch.running = False
            return WaitState.RUNNING
        branch.complete = True
        index -= 1
    return WaitState.FINISH


class Job:
    def __init__(self, job_branches, job_number):
        self.branches = job_branches.copy()
        self.number = job_number
        self.pgid = job_branches[0].pgid
        self.command = job_branches[-1].command

    @classmethod
    def create_new_index(cls, job_list):
        nbr_jobs = len(job_list)
        index = 0
        while index < nbr_jobs:
            job = job_list[index]
            if job.number > index:
                return index
            index += 1
        return index

    @classmethod
    def sort_jobs(cls, job_list):
        def sort_fct(job): return job.number
        job_list.sort(key=sort_fct)


class BackgroundJobs:
    def __init__(self):
        self.list_jobs = []
        self.allow_background = True

    def add_job(self, job_branches):
        """Add a new process in the background process group"""
        job_index = Job.create_new_index(self.list_jobs)
        new_job = Job(job_branches, job_index)
        self.list_jobs.append(new_job)
        Job.sort_jobs(self.list_jobs)
        print("[{}] {}".format(job_index, job_branches[0].pgid))

    def __str__(self):
        return str(self.list_jobs)

    def is_running(self, job_id):
        """
        Check if any process in the job is still running or if it's
        already finish.
        """
        job = self.get_job(job_id)
        return analyse_job_status(job.branches, mode=os.WNOHANG | os.WUNTRACED)

    def remove(self, job_id):
        nbr_jobs = len(self.list_jobs)
        index = 0
        while index < nbr_jobs:
            job = self.list_jobs[index]
            if job.number == job_id:
                self.list_jobs.pop(index)
                return
            index += 1

    def get_job(self, job_id):
        nbr_jobs = len(self.list_jobs)
        index = 0
        while index < nbr_jobs:
            job = self.list_jobs[index]
            if job.number == job_id:
                return job
            index += 1
        return None

    def clear(self):
        self.list_jobs.clear()

    def relaunch(self, job_id):
        """
        Push a job in foreground and send him SIGCONT.
        Keep it in the background job list if it's suspended.
        """
        if self.is_running(job_id) == WaitState.FINISH:
            print("tmpsh: fg: job has terminated")
            self.remove(job_id)
            return
        job = self.get_job(job_id)
        fg.set_foreground(job.pgid)
        os.kill(-job.pgid, signal.SIGCONT)
        job.branches[0].running = True
        print(job.command)
        if analyse_job_status(job.branches) == WaitState.FINISH:
            self.remove(job_id)
            print("[{}] + {} continued".format(job_id, job.pgid))
        else:
            print("[{}] + Suspended.".format(job_id))
        fg.set_foreground(os.getpgrp())
        fg.restore_tcattr()

    def wait_zombie(self):
        """
        Called before giving back the prompt to the user.
        Check if some jobs are done and remove them from the current joblist.
        """
        index = 0
        nbr_job = len(self.list_jobs)
        while index < nbr_job:
            job = self.list_jobs[index]
            if self.is_running(job.number) == WaitState.FINISH:
                print("[{}] + Done {}".format(job.number, job.command))
                self.remove(job.number)
                nbr_job -= 1
                index -= 1
            index += 1
