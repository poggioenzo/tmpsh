#!/usr/bin/env python3

from utils.readgrammar import ShellGrammar
global GRAMMAR
GRAMMAR = ShellGrammar()

def ops_begin_with(pattern, ops):
	i = len(pattern)
	for op in ops:
		if pattern == op[:i]:
			return True
	return False

def add_token(current, tokens):
	if current != "":
		tokens.append(current)
		current = ""
	return current

def span(command, tokens, current):
	j = 1
	i = 1
	length_cmd = len(command)
	while j <= GRAMMAR.maxlen_leaf_op and j <= length_cmd:
		if ops_begin_with(command[:j], GRAMMAR.leaf_op):
			j += 1
		else:
			break
	j -= 1
	if command[:j] in GRAMMAR.leaf_op:
		tokens.append(command[:j])
		i = j
	else:
		current.append(command[0])
	return i

def span_space(command, tokens):
	i = 0
	length_cmd = len(command)
	while (i < length_cmd and command[i] in GRAMMAR.spaces):
		i += 1
	tokens.append(command[:i])
	return i

def tokenize(command, tokens):
	length_cmd = len(command)
	current = ""
	i = 0
	while i < length_cmd:
		if ops_begin_with(command[i], GRAMMAR.leaf_op):
			current = add_token(current, tokens)
			tmp_current = []
			i += span(command[i:],  tokens, tmp_current)
			if len(tmp_current) == 1:
				current += tmp_current[0]
		elif command[i] == GRAMMAR.escape:
			i += 1
			if i < length_cmd:
				current += GRAMMAR.escape + command[i]
			else:
				current += GRAMMAR.escape
			i += 1
		elif command[i] in GRAMMAR.spaces:
			current = add_token(current, tokens)
			i += span_space(command[i:], tokens)
		else:
			current += command[i]
			i += 1
	add_token(current, tokens)
