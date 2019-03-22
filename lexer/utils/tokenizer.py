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

def atomize(command, singlechars):
	list_tokens_atomic = []
	curr_token = ""
	while command:
		actual = command.popleft()
		if not actual in ' \t' :
			if actual in singlechars:
				if curr_token != "":
					list_tokens_atomic.append(curr_token)
					curr_token = ""
				list_tokens_atomic.append(actual)
			else:
				curr_token += actual
		else:
			if curr_token != "":
				list_tokens_atomic.append(curr_token)
				curr_token = ""
	if curr_token != "":
		list_tokens_atomic.append(curr_token)
	list_tokens_atomic = dq(list_tokens_atomic)
	return list_tokens_atomic


def containalphanum(key):
	return any([l.isalnum() for l in key])

def get_singlechars(rev_gra_keys):
	singlechars = set(''.join([k for k in rev_gra_keys
			if not containalphanum(k)]))
	singlechars.discard('.')
	singlechars.add('\n')
	return singlechars

def get_atomic_op(rev_gra_keys):
	atomic_op = [k for k in rev_gra_keys if not containalphanum(k)]
	atomic_op.append('\n')
	compose_op = [k for k in atomic_op if "." in k]
	for k in compose_op:
		atomic_op.remove(k)
		atomic_op.extend(k.split('.'))
	return atomic_op



def list_begin_op(atomic_op, begin_op):
	len_op = len(begin_op)
	return [op for op in atomic_op if op[:len_op] == begin_op]

def recompose_op(list_tokens_atomic, atomic_op):
	list_tokens = []
	while list_tokens_atomic:
		actual = list_tokens_atomic.popleft()
		if len(actual) > 1:
			list_tokens.append(actual)
			actual = ""
		else:
			op = ""
			while 1:
				list_op = list_begin_op(atomic_op, op + actual)
				if list_op == []:
					list_tokens.append(op)
					break
				op += actual
				if list_tokens_atomic:
					actual = list_tokens_atomic.popleft()
		if actual != "":
			list_tokens.append(actual)
			actual = ""
	return list_tokens

def tokenize(command, grammar):
	rev_gra = get_reverse_grammar(grammar)
	singlechars = get_singlechars(rev_gra.keys())
	list_tokens_atomic = atomize(command, singlechars)
	atomic_op = get_atomic_op(rev_gra.keys())
	tokens = recompose_op(list_tokens_atomic, atomic_op)
	return tokens
