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
         'loop2': 'echo ok; loop3',
         'loop3': 'loop1',
         'dit': 'echo ',
         'bonjour': 'salut connard',
         'redit': 'echo je me repete; '}

ENVIRON = os.environ.copy()
PASSED_ALIAS = []
PREVIOUS_PASSED_ALIAS = []
STILL_ALIASING = True
REPLACE = False


LOCAL_VAR = {}
LAST_STATUS = 0
MAXIMAL_DEPTH_LIMIT = 10
MAXIMAL_DEPTH_ITER = 0


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
