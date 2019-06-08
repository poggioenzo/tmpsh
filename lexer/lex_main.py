#!/usr/bin/env python3

import sys
# import code
# from utils.commands2 import ListCommands
from utils.tagstokens import TagsTokens


def main():
    if len(sys.argv) == 1:
        tt = TagsTokens(
            "ls -l; echo 'lol' 1;$(echo ls) \\\ncat ../*")
    else:
        tt = TagsTokens(" ".join(sys.argv[1:]))
    print(tt)


if __name__ == '__main__':
    main()
