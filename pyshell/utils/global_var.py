from utils.shellgrammar import ShellGrammar
from utils.execution.job_control import BackgroundJobs
import termios
import sys
import os

GRAMMAR = ShellGrammar()
ALIAS = {'all': 'ls -l', 'gall': 'all -G -1', 'ball': '$(gall)',
         'recursion1': 'recursion2',
         'recursion2': 'recursion3',
         'loop1': 'loop2',
         'loop2': 'loop3',
         'loop3': 'loop1'}

ENVIRON = os.environ.copy()
LOCAL_VAR = {}
LAST_STATUS = 0

JOBS = BackgroundJobs()
TCSETTINGS = termios.tcgetattr(sys.stdin.fileno())
CEXTENSION = None

try:
    debug_file = "/dev/ttys003"
    DEBUG = open(debug_file, "w")
except PermissionError:
    print("No able to open debug file {}".format(debug_file))

def dprint(string, *args, **kwargs):
    #Small debug function to print with DEBUG filestream
    print(string, *args, file=DEBUG, **kwargs, flush=True)
