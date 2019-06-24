#!/usr/bin/env python3

import sys
from utils.tagstokens import TagsTokens

if __name__ == '__main__':
    if len(sys.argv) == 1:
        ENTRY = '"$(lol)"'
    else:
        ENTRY = " ".join(sys.argv[1:])
    TAGSTOKENS = TagsTokens()
    TAGSTOKENS.init_with_input(ENTRY, 0, False)
    TAGSTOKENS.check_syntax()
    print(TAGSTOKENS)
