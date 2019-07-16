from utils.shellgrammar import ShellGrammar
from utils.job_control import BackgroundJobs
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
