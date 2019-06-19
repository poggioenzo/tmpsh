#!/usr/bin/env python3

from cmd import Cmd
from utils.tagstokens import TagsTokens
from utils.ast import AST
from utils.execute import Executor
from utils.global_var import ENVIRON
import os, sys

class Prompt(Cmd):
    intro = "tmpsh - Total Mastering Professional Shell"
    prompt = "a prompt > "
    content = ""
    def default(self, line):
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

def main(argc, argv, environ):
    ENVIRON = environ.copy()
    Prompt().cmdloop()



if __name__ == "__main__":
    main(len(sys.argv), sys.argv, os.environ)
