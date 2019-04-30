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

    # code.interact(local = locals())
    # print([ lc.tokens[x.start:x.end] for x in lc.tree_commands])
    # print([ (x.start,x.end) for x in lc.tree_commands])
    # print([(x.sub[0].start, x.sub[0].end) if x.sub != [] else
        # () for x in lc.tree_commands ])
    # print([x.sub for x in lc.tree_commands])

if __name__ == '__main__':
    main()
