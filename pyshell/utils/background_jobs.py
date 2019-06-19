#!/usr/bin/env python3

class BackgroundJobs:
    def __init__(self):
        self.list_jobs = []

    def add_job(self, pid, command):
        """Add a new process in the background process group"""
        self.list_jobs.append((pid, command))
