#!/usr/bin/env python3

import sys
from utils.tagstokens import TagsTokens as TT
from utils.ast import AST

if __name__ == '__main__':
    if len(sys.argv) == 1:
        ENTRY = "p3 <(ls $((echo ${PATH}|| cat list_path )| sed 's/:/\ /g') | grep $( echo \"py\")) >> test_py"
        print(ENTRY)
    else:
        ENTRY = " ".join(sys.argv[1:])
    TAGSTOKENS = TT().init_with_input(ENTRY).check_syntax()
    if TAGSTOKENS.valid and not TAGSTOKENS.incomplete:
        TREE = AST(TAGSTOKENS)
        print(TREE)
    elif TAGSTOKENS.incomplete:
        print('Close all this opened command tags: {}'.format(
            str(TAGSTOKENS.stack)))
    else:
        print('Close all this command tokens: {}'.format(
            str(TAGSTOKENS.token_error)))
