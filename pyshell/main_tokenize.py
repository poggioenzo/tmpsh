#!/usr/bin/env python3

import sys
import utils.tokenizer as tk

if __name__ == '__main__':
    if len(sys.argv) == 1:
        ENTRY = '" $()"  '
    else:
        ENTRY = " ".join(sys.argv[1:])
    TOKENS = []
    tk.tokenize(ENTRY, TOKENS)
    print(TOKENS)
