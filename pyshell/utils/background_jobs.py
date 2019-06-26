#!/usr/bin/env python3

import os

class BackgroundJobs:
    def __init__(self):
        self.list_jobs = []

    def add_job(self, pid, command):
        """Add a new process in the background process group"""
        self.list_jobs.append((pid, command))

    def __iter__(self):
        self.index = 0
        return iter(self.list_jobs)

    def __next__(self):
        jobs = self.list_jobs[self.index]
        self.index += 1
        return jobs

    def __str__(self):
        return str(self.list_jobs)

    def wait_zombie(self):
        index = 0
        nbr_job = len(self.list_jobs)
        index_to_del = []
        print(nbr_job)
        while index < nbr_job:
            job_pid = self.list_jobs[index][0]
            task = self.list_jobs[index][1]
            print(job_pid)
            try:
                status = os.waitpid(job_pid, os.WNOHANG)
            except Exception as Error:
                print("Error for ", job_pid)
                index += 1
                continue
            if status[0] != 0:
                index_to_del.append(index)
                print("[{}] + Done {}".format(index, task))
            index += 1
        index = 0
        nbr_deletion = len(index_to_del)
        while index < nbr_deletion:
            deletion_index = nbr_deletion[index]
            del self.list_jobs[deletion_index - index]
            index += 1
