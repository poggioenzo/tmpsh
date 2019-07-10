#!/usr/bin/env python3

from cmd import Cmd
from utils.tagstokens import TagsTokens
from utils.ast import AST
from utils.execute import Executor
from utils.global_var import ENVIRON
import os, sys
import string
import signal

class Prompt(Cmd):
    intro = "tmpsh - Total Mastering Professional Shell"
    prompt = "a prompt > "
    content = ""
    def default(self, line):
        line = [char for char in line if char in string.printable]
        line = "".join(line)
        self.content += line
        TAGSTOKENS = TagsTokens().init_with_input(line)#.check_syntax()
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

def init_shell():
    signal.signal(signal.SIGTSTP, signal.SIG_IGN)
    signal.signal(signal.SIGTTIN, signal.SIG_IGN)
    signal.signal(signal.SIGTTOU, signal.SIG_IGN)

def main(argc, argv, environ):
    init_shell()
    ENVIRON = environ.copy()
    Prompt().cmdloop()



if __name__ == "__main__":
    main(len(sys.argv), sys.argv, os.environ)
