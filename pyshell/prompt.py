#!/usr/bin/env python3

from cmd import Cmd
from utils.tagstokens import TagsTokens
from utils.ast import AST
from utils.execute import Executor
import utils.global_var as gv
import utils.execution.tmpsh_signal as tmpsh_signal
from utils.execution.job_control import BackgroundJobs
import os, sys
import string
import signal
import termios
import ctypes

class Prompt(Cmd):
    intro = "tmpsh - Total Mastering Professional Shell"
    prompt = "a prompt > "
    content = ""
    def default(self, line):
        line = [char for char in line if char in string.printable]
        line = "".join(line)
        self.content += line
        TAGSTOKENS = TagsTokens().init_with_input(line).check_syntax()
        if TAGSTOKENS.valid and not TAGSTOKENS.incomplete:
            TREE = AST(TAGSTOKENS)
            run = Executor(TREE)
            self.content = ""
        elif TAGSTOKENS.incomplete:
            self.prompt = "{} > ".format(' '.join([tag.lower() for tag in TAGSTOKENS.stack]))
        else:
            print('Close all this command tokens: {}'.format(
                str(TAGSTOKENS.token_error)))
            self.prompt = "error prompt > "

    def do_EOF(self, line):
        exit(1)

def load_extension():
    file_list = ["utils/execution/sigmask_modif.c"]
    file_str = " ".join(file_list)
    library = "utils/execution/sigmask.so"
    os.system("gcc -shared {} -o {}".format(file_str, library))
    return ctypes.cdll.LoadLibrary(library)

def main(argc, argv, environ):
    gv.JOBS = BackgroundJobs()
    gv.CEXTENSION = load_extension()
    tmpsh_signal.init_signals()
    prompt = Prompt()
    while True:
        try:
            prompt.cmdloop()
        except KeyboardInterrupt:
            print("")
            prompt.intro = ""
            pass

if __name__ == "__main__":
    main(len(sys.argv), sys.argv, os.environ)
