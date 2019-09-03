from utils.shellgrammar import ShellGrammar
import termios
import sys
import os

GRAMMAR = ShellGrammar()
ALIAS = {'all': 'ls -l\t', 'gall': 'all -G -1', 'ball': '$(gall)',
         'another': 'ls\t',
         'recursion1': 'recursion2',
         'recursion2': 'recursion3',
         'loop1': 'loop2',
         'loop2': 'loop3',
         'loop3': 'echo ok ; loop1',
         # 'loop4': 'echo ok && loop2',
         'dit': 'echo ',
         'bonjour': 'salut connard',
         'redit': 'echo je me repete; dit'}

ENVIRON = os.environ.copy()
PASSED_ALIAS = []
ACTUAL_ALIAS = []
ALIASINDEPTH = 0

LOCAL_VAR = {}
LAST_STATUS = 0

DONTPRINT = True

HEREDOCS = []

JOBS = None
HASH = {}

with open("/dev/tty") as term:
    TCSETTINGS = termios.tcgetattr(term.fileno())
CEXTENSION = None

try:
    debug_file = "/dev/ttys003"
    DEBUG = open(debug_file, "w")
except PermissionError:
    pass
    # print("No able to open debug file {}".format(debug_file))


def dprint(string, *args, **kwargs):
    # Small debug function to print with DEBUG filestream
    print(string, *args, file=DEBUG, **kwargs, flush=True)
