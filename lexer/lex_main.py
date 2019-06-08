#!/usr/bin/env python3

import sys
# import code
# from utils.commands2 import ListCommands
from utils.tagstokens import TagsTokens

if __name__ == '__main__':
    if len(sys.argv) == 1:
        TAGSTOKENS = TagsTokens().init_with_input(
            "ls -l; echo 'lol' 1;$(echo ls) \\\ncat ../*")
    else:
        TAGSTOKENS = TagsTokens().init_with_input(" ".join(sys.argv[1:]))
    print(TAGSTOKENS)
