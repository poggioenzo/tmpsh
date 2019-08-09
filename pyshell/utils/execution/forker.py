import utils.global_var as gv
import os
import sys
from utils.execution.foreground import set_foreground

def fork_prepare(pgid=0, background=True):
    """
    Fork a new process, and prepare the process to be in foreground
    or in background.
    """
    pid = os.fork()
    if gv.JOBS.allow_background == True:
        os.setpgid(pid, pgid)
        if background == False:
            set_foreground(os.getpgid(pid))
    return pid
