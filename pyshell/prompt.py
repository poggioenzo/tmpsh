#!/usr/bin/env python3

from cmd import Cmd
from utils.tagstokens import TagsTokens
from utils.ast import AST
from utils.execute import Executor
from utils.global_var import ENVIRON, TCSETTINGS
import utils.tmpsh_signal as tmpsh_signal
import os, sys
import string
import signal
import termios

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
    def do_EOF(self, line):
        print("XEOF {}: {}".format(line, os.getpid()))
        print("pgid {} pid {} tpgid {}".format(os.getpgid(0), os.getpid(), os.tcgetpgrp(0)))
        content = sys.stdin.read()
        print("get : |{}|".format(content))
        exit(1)


def main(argc, argv, environ):
    tmpsh_signal.init_signals()

    Prompt().cmdloop()



if __name__ == "__main__":
    main(len(sys.argv), sys.argv, os.environ)
