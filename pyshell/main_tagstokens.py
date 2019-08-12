#!/usr/bin/env python3

import sys
from utils.tagstokens import TagsTokens

if __name__ == '__main__':
    if len(sys.argv) == 1:
        # ENTRY = "ls -l; echo 'lol' 1;$(echo ls) \\\ncat ../*"
        # ENTRY = "echo $PATH\\ "
        ENTRY = ''' ls
<< EOF << EOF
'quote'
$('quote " ')
EOF
"dquote" $("$(dquote)"; (lol)) stmt
EOF
<< EOF << EOF
EOF
EOF
'''
    else:
        ENTRY = " ".join(sys.argv[1:])
    TAGSTOKENS = TagsTokens().init_with_input(ENTRY).check_syntax()
    print(TAGSTOKENS)
