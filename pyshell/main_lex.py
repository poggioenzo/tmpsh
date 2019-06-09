#!/usr/bin/env python3

import sys
# import code
# from utils.commands2 import ListCommands
from utils.tagstokens import TagsTokens
import utils.shift_reduce as sr
import utils.global_var as gv

if __name__ == '__main__':
    if len(sys.argv) == 1:
        ENTRY = "ls -l; echo 'lol' 1;$(echo ls) \\\ncat ../*"
    else:
        ENTRY = " ".join(sys.argv[1:])
    TAGSTOKENS = TagsTokens().init_with_input(ENTRY)
    print(TAGSTOKENS)
    print(sr.shift_reduce(TAGSTOKENS.tags, gv.GRAMMAR))
