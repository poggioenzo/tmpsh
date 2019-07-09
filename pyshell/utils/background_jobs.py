#!/usr/bin/env python3

import os
import enum

class WaitState(enum.Enum):
    FINISH = 0
    RUNNING = 1

class BackgroundJobs:
    def __init__(self):
        self.list_jobs = []

    def add_job(self, pid, command, pipes_pid):
        """Add a new process in the background process group"""
        self.list_jobs.append((pid, command, pipes_pid))

    def __iter__(self):
        self.index = 0
        return iter(self.list_jobs)

    def __next__(self):
        jobs = self.list_jobs[self.index]
        self.index += 1
        return jobs

    def __str__(self):
        return str(self.list_jobs)

    def wait_job_pipe(self, job_index):
        job_pid, command, pipes_pids = self.list_jobs[job_index]
        pipe_index = 0
        nbr_pipe = len(pipes_pids)
        while pipe_index < nbr_pipe:
            pid_to_check = pipes_pids[pipe_index]
            status = os.waitpid(pid_to_check, os.WNOHANG)
            if status[0] != 0:
                pipes_pids.remove(pid_to_check)
                nbr_pipe -= 1
                continue
            pipe_index += 1
        if len(pipes_pids) == 0:
            return WaitState.FINISH
        return WaitState.RUNNING

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
            if self.wait_job_pipe(index) == WaitState.RUNNING:
                index += 1
                continue
            job_pid = self.list_jobs[index][0]
            task = self.list_jobs[index][1]
            status = os.waitpid(job_pid, os.WNOHANG)
            if status[0] != 0:
                index_to_del.append(index)
                print("[{}] + Done {}".format(index, task))
            index += 1
        index = 0
        #Finally, remove from our joblist those which are over.
        nbr_deletion = len(index_to_del)
        while index < nbr_deletion:
            deletion_index = index_to_del[index]
            del self.list_jobs[deletion_index - index]
            index += 1
