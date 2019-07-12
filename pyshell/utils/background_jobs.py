#!/usr/bin/env python3

import os
import enum
import time
import signal
import termios

class WaitState(enum.Enum):
    FINISH = 0
    RUNNING = 1

class Job:
    def __init__(self, pid, command, job_pipeline):
        self.pid = pid
        self.command = command
        self.status = 0
        self.complete = False
        self.pipeline = job_pipeline
        self.pgid = os.getpgid(self.pid)

    def wait_job_pipe(self):
        """
        Check if some pipes of the jobs are still running.
        Wait each pipe of the job, and remove them from the pipeline
        list if they are over.
        """
        pipe_index = 0
        nbr_pipe = len(self.pipeline)
        while pipe_index < nbr_pipe:
            pid_to_check = self.pipeline[pipe_index]
            status = os.waitpid(pid_to_check, os.WNOHANG)
            if status[0] != 0:
                self.pipeline.remove(pid_to_check)
                nbr_pipe -= 1
                continue
            pipe_index += 1
        if len(self.pipeline) == 0:
            return WaitState.FINISH
        return WaitState.RUNNING

    def is_running(self):
        """
        Check if the given jobs is still running. Verify each piped process of the
        job and the background command herself.
        """
        if self.complete == False:
            status = os.waitpid(self.pid, os.WNOHANG)
            if status[0] != 0:
                self.complete = True
        if self.wait_job_pipe() == WaitState.FINISH and self.complete == True:
            return WaitState.FINISH
        return WaitState.RUNNING

    def push_foreground(self):
        #Check if the job is already over
        if self.is_running == WaitState.FINISH:
            print("tmpsh: fg: job has terminated", file=sys.stderr)
            return
        os.tcsetpgrp(0, self.pgid)
        attributes = termios.tcgetattr(0)
        if self.complete == False:
            os.kill(self.pid, signal.SIGCONT)
        while self.complete == False or len(self.pipeline) > 0:
            #Choose if we need to check the job program, or program in the pipeline
            if self.complete == False:
                child_pid, status = os.waitpid(self.pid, os.WUNTRACED)
            else:
                child_pid, status = os.waitpid(self.pipeline[0], os.WUNTRACED)
            #if the waited program is over, behave properly to avoid waiting
            #it twice.
            if os.WIFSTOPPED(status) == True:
                os.tcsetpgrp(0, os.getpgrp())
                termios.tcsetattr(0, termios.TCSADRAIN, attributes)
                return WaitState.RUNNING
            elif os.WIFEXITED(status) or os.WIFSIGNALED(status):
                if child_pid == self.pid:
                    self.complete = True
                else:
                    self.pipeline.pop(0)
        os.tcsetpgrp(0, os.getpgrp())
        termios.tcsetattr(0, termios.TCSADRAIN, attributes)
        return WaitState.FINISH


class BackgroundJobs:
    def __init__(self):
        self.list_jobs = []

    def add_job(self, pid, command, pipes_pid):
        """Add a new process in the background process group"""
        new_job = Job(pid, command, pipes_pid.copy())
        self.list_jobs.append(new_job)
        pipes_pid.clear()

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
        job = self.list_jobs[index]
        return job.is_running()

    def remove(self, index):
        self.list_jobs.pop(index)

    def relaunch(self, index):
        job = self.list_jobs[index]
        if job.push_foreground() == WaitState.FINISH:
            self.remove(index)

    def clear(self):
        self.list_jobs.clear()



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
            job = self.list_jobs[index]
            if job.is_running() == WaitState.FINISH:
                index_to_del.append(index)
                print("[{}] + Done {}".format(index, job.command))
            index += 1
        index = 0
        #Finally, remove from our joblist those which are over.
        nbr_deletion = len(index_to_del)
        while index < nbr_deletion:
            deletion_index = index_to_del[index]
            del self.list_jobs[deletion_index - index]
            index += 1

