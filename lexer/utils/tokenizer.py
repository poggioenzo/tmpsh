#!/usr/bin/env python3

from pprint import pprint
from collections import namedtuple
from collections import deque as dq
BeginEnd = namedtuple('Token', ['lol', 'end'])

def get_reverse_grammar(grammar):
	reverse_grammar = {}
	for key in grammar:
		for value in grammar[key]:
			reverse_grammar[value] = key
	return reverse_grammar


def stack_until(chars, endchar):
	pass





def spliter(command):
	pass



def tokenize(command, grammar):
	rev_gra = get_reverse_grammar(grammar)
	command_chars = dq(command)
	listtok = []
	token = []
	pprint(rev_gra)
	# while(command_chars):
	# 	actual = command_chars.popleft()
	# 	if actual in ' \n' and token != [] :
	# 		listtok.append("".join(token))
	# 		token = []
	# 	elif actual in '\\&"<+;>\'|)=(:
	# 	else:
	# 		token.append(actual)
	# if token != []:
	# 	listtok.append("".join(token))
	print(listtok)
