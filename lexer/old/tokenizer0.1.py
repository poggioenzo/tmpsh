#!/usr/bin/env python3

from utils.readgrammar import ShellGrammar
global GRAMMAR
GRAMMAR = ShellGrammar()

def ops_begin_with(pattern, ops):
	i = len(pattern)
	return any([pattern == op[:i] for op in ops])

def trueXor(argv):
    return sum(argv) == 1

def add_token(current, tokens):
	if current != "":
		tokens.append(current)
		current = ""
	return current

def span_sub(command, tokens, current, top=1):
	i = 0
	j = 1
	length_cmd = len(command)
	while j <= GRAMMAR.maxlen_opening_op and i == 0:
		if command[:j] in GRAMMAR.opening_op:
			key = command[:j]
			i += j
			while i < length_cmd:
				if command[i] == GRAMMAR.escape:
					i += 1
				elif command[i] == GRAMMAR.opening_op[key][0]:
					break
				elif command[i] in GRAMMAR.begin_opening_op:
					i += span_sub(command[i:], tokens, current, 0)
				i += 1
		j += 1
	if top:
		if i > 0:
			tokens.append(command[:i+1])
		else:
			current.append(command[0])
		i += 1
	return i

def span_op(command, tokens, current):
	j = 1
	length_cmd = len(command)
	while j <= GRAMMAR.maxlen_atomic_op and j <= length_cmd:
		if ops_begin_with(command[:j], GRAMMAR.atomic_op):
			j += 1
		else:
			break
	j -= 1
	if command[:j] in GRAMMAR.atomic_op:
		tokens.append(command[:j])
	else:
		current.append(command[0])
		j = 1
	return j

def select_span(command, tokens, current, selection):
	i = 0
	if selection[0]:
		i = span_op(command, tokens, current)
	else:
		i = span_sub(command, tokens, current)
	return i

def span(command, tokens, current):
	j = 0
	i = 1
	length_cmd = len(command)
	maxlen = max(GRAMMAR.maxlen_atomic_op, GRAMMAR.maxlen_opening_op)
	while j < length_cmd and j < maxlen :
		j += 1
		selection = [
			ops_begin_with(command[:j], GRAMMAR.atomic_op),
			ops_begin_with(command[:j], GRAMMAR.opening_op)
		]
		if trueXor(selection):
			i = select_span(command, tokens, current, selection)
			break
	if sum(selection) == 0:
		current.append(command[0])
	return i

def tokenize(command, tokens):
	length_cmd = len(command)
	current = ""
	i = 0
	while i < length_cmd:
		if command[i] in GRAMMAR.begin_op :
			current = add_token(current, tokens)
			tmp_current = []
			i += span(command[i:],  tokens, tmp_current)
			if len(tmp_current) == 1:
				current += tmp_current[0]
		elif command[i] == GRAMMAR.escape:
			i += 1
			if i < length_cmd:
				current += command[i]
			i += 1
		elif command[i] in ' \r\t':
			current = add_token(current, tokens)
			i += 1
		else:
			current += command[i]
			i += 1
	add_token(current, tokens)
