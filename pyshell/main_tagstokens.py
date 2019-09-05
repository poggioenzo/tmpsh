#!/usr/bin/env python3

import sys
from utils.tagstokens import TagsTokens

if __name__ == '__main__':
    if len(sys.argv) == 1:
        # ENTRY = "ls -l; echo 'lol' 1;$(echo ls) \\\ncat ../*"
        ENTRY = "echo $PATH\\ "
        ENTRY = '''
        echo ~ ~te~st" ~ '$USER \""+\\$USER+$US\ER~$USERS' ~ t"e$USER \\'~'' ""'`' ""' \\' ""'" \\'"
        '''
        # ENTRY = '<<-EOF\n\t lol\n\t\tlol\nEOF'
        # print(ENTRY)
    else:
        ENTRY = " ".join(sys.argv[1:])
    TAGSTOKENS = TagsTokens().init_with_input(ENTRY).check_syntax()
    i = 0
    while i < TAGSTOKENS.length:
        print([TAGSTOKENS.tags[i], TAGSTOKENS.tokens[i]])
        i += 1
    print(TAGSTOKENS)
