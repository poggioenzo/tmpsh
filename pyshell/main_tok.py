#!/usr/bin/env python3

import sys
from utils.commands import ListCommands


if __name__ == '__main__':
    if len(sys.argv) > 1:
        COMMAND = " ".join(sys.argv[1:])
        COMMAND = ListCommands(COMMAND)
        print(COMMAND.tokens)
    else:
        print("missing command.")
