#!/usr/bin/env python3

import sys
from utils.tagstokens import TagsTokens

if __name__ == '__main__':
    if len(sys.argv) == 1:
        # ENTRY = "ls -l; echo 'lol' 1;$(echo ls) \\\ncat ../*"
        ENTRY = "echo $PATH\\ "
        ENTRY = ''' ls
<< EOF << EOF
'quote'
$('quote " ')
EOF





    lol


    "dquote" $("$(dquote)"; (lol)) stmt
EOF
<<- $(  LOL  ) <<- 'EOF'


\t\t
     lol



        $(  LOL  )
        python3 lol.py $(
    EOF
global_var
'''
        # ENTRY = '<<-EOF\n\t lol\n\t\tlol\nEOF'
        # print(ENTRY)
    else:
        ENTRY = " ".join(sys.argv[1:])
    TAGSTOKENS = TagsTokens().init_with_input(ENTRY).check_syntax()
    print(TAGSTOKENS)
