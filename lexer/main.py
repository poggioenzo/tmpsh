#!/usr/bin/env python3


import utils.readgrammar as rg
import utils.tokenizer as tk
import utils.file as fl
import sys
from collections import deque as dq

from pprint import pprint

def main():
	grammar = rg.get_grammar("grammar.txt")
	if len(sys.argv) > 1:
		command = " ".join(sys.argv[1:])
		tokens = []
		tk.tokenize(command, grammar, tokens)
		print(tokens)
	else:
		print("missing command.")




if __name__ == '__main__':
	main()
