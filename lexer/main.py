#!/usr/bin/env python3


import utils.readgrammar as rg
import utils.tokenizer as tk
import utils.file as fl
import sys

from pprint import pprint

def main():
	grammar = rg.get_grammar("grammar.txt")
	# pprint(grammar)
	if len(sys.argv) > 1:
		command = " ".join(sys.argv[1:])
		print(command)
		tokens = tk.tokenize(command, grammar)




if __name__ == '__main__':
	main()
