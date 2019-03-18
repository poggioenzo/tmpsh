#!/usr/bin/env python3

from pprint import pprint
from collections import deque as dq

def get_reverse_grammar(grammar):
	reverse_grammar = {}
	for key in grammar:
		for value in grammar[key]:
			reverse_grammar[value] = key
	return reverse_grammar


def tokenize(command, grammar):
	rev_gra = get_reverse_grammar(grammar)
	command_chars = dq(command)
