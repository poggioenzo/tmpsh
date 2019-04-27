#!/usr/bin/env python3

def incomplete_key(stack, grammar):
	# TODO
	return False

def keyinstack(stack, grammar):
	len_stack = len(stack)
	i = 0
	while i < len_stack:
		key = ' '.join(stack[i:])
		if key in grammar.reverse:
			return i
		i += 1
	return -1

def reduce(stack, instack, grammar):
	return (stack[:instack] + [grammar.reverse[' '.join(stack[instack:])]])

def reduce_all(stack, instack, grammar):
	while instack > -1:
		stack = reduce(stack, instack, grammar)
		instack = keyinstack(stack, grammar)
	return stack

def reduce_shift(tags, grammar):
	stack = []
	i = 0
	len_tags = len(tags)
	while (i < len_tags):
		instack = keyinstack(stack, grammar)
		if instack > -1:
			stack = reduce_all(stack, instack, grammar)
		else :
			if tags[i] == 'SPACES':
				pass
			else:
				stack.append(tags[i])
			i += 1
	instack = keyinstack(stack, grammar)
	if instack > -1:
		stack = reduce_all(stack, instack, grammar)
	return stack
