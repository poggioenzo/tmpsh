#!/usr/bin/env python3

import sys
# import code
from utils.commands import ListCommands


def main():
    if len(sys.argv) == 1:
        list_command = ListCommands(
            "ls -l; echo 'lol' 1;$(echo ls) \\\ncat ../*")
    else:
        list_command = ListCommands(" ".join(sys.argv[1:]))

    print(list_command)

if __name__ == '__main__':
    main()
