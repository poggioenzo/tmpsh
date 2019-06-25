#!/usr/bin/env python3


import sys
from pprint import pprint
import utils.shiftreduce as sr
from utils.grammar import Grammar
GRAMMAR = Grammar("grammar/grammar_test.txt")


if __name__ == '__main__':
    if len(sys.argv) == 1:
        ENTRY = 'E E'
    else:
        ENTRY = " ".join(sys.argv[1:]).upper()
    pprint(GRAMMAR.grammar)
    print(sr.shift_reduce(ENTRY.split(), GRAMMAR))
