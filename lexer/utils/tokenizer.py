#!/usr/bin/env python3


def trueXor(argv):
    return sum(argv) == 1

def add_token(current, tokens):
	if current != "":
		tokens.append(current)
		current = ""
	return current

def span_sub(command, grammar, tokens, top=1):
	i = 0
	j = 1
	length_cmd = len(command)
	while j <= grammar.maxlen_opening_op and i == 0:
		if command[:j] in grammar.opening_op:
			key = command[:j]
			i += j
			while i < length_cmd:
				if command[i] == grammar.escape:
					i += 1
				elif command[i] == grammar.opening_op[key][0]:
					break
				elif command[i] in grammar.begin_opening_op:
					i += span_sub(command[i:], grammar, tokens, 0)
				i += 1
		j += 1
	if i >= 0 and top:
		i += 1
		tokens.append(command[:i])
	return i

def span_op(command, grammar, tokens):
	j = 1
	length_cmd = len(command)
	while j <= grammar.maxlen_atomic_op and j <= length_cmd:
		if command[:j] in grammar.atomic_op:
			j += 1
		else:
			break
	j -= 1
	if command[:j] in grammar.atomic_op:
		tokens.append(command[:j])
	return j

def select_span(command, grammar, tokens, selection):
	i = 0
	if selection[0]:
		i = span_op(command, grammar, tokens)
	else:
		i = span_sub(command, grammar, tokens)
	return i

def span(command, grammar, tokens, current):
	j = 0
	i = 1
	length_cmd = len(command)
	maxlen = max(grammar.maxlen_atomic_op, grammar.maxlen_opening_op)
	while j < length_cmd and j < maxlen :
		j += 1
		selection = [
			command[:j] in grammar.atomic_op,
			command[:j] in grammar.opening_op,
			command[:j] in grammar.begin_opening_op
		]
		if trueXor(selection):
			i = select_span(command, grammar, tokens, selection)
			break
	if sum(selection) == 0:
		current.append(command[0])
	return i

def tokenize(command, grammar, tokens):
	length_cmd = len(command)
	current = ""
	i = 0
	while i < length_cmd:
		if command[i] in grammar.begin_op :
			current = add_token(current, tokens)
			tmp_current = []
			i += span(command[i:], grammar, tokens, tmp_current)
			if len(tmp_current):
				current += tmp_current[0]
		elif command[i] == grammar.escape:
			i += 1
			current += command[i]
			i += 1
		elif command[i] in ' \r\t':
			current = add_token(current, tokens)
			i += 1
		else:
			current += command[i]
			i += 1
	add_token(current, tokens)
