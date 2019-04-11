#!/usr/bin/env python3

from pprint import pprint
import utils.file as fl


def get_grammar_from_path(path):
	text = fl.get_text(path)
	lines = text.split('\n')
	length = len(lines)
	i = 0
	grammar = {}
	while (i < length):
		if len(lines[i]) > 0 and lines[i][0] not in '\n#\t':
			keyword = lines[i].split(':')[0].strip()
			i += 1
			if keyword not in grammar:
				grammar[keyword] = []
			while (1):
				if len(lines[i]) > 0 and lines[i][0] == '\t':
					grammar[keyword].append(lines[i].strip())
				else:
					break
				i += 1
		i += 1
	return grammar

def get_reverse_grammar(grammar):
	reverse_grammar = {}
	for key in grammar:
		for value in grammar[key]:
			reverse_grammar[value] = key
	return reverse_grammar

def containalphanum(key):
	return any([l.isalnum() for l in key])

# def containupper(key):
# 	return any([l.isupper() for l in key])
# useless because if while for are RESERVED_WORD

def get_list_op(reverse):
	return [key for key in reverse if not containalphanum(key)]

def get_atomic_compose_op(reverse):
	atomic_op = get_list_op(reverse)
	compose_op = [k for k in atomic_op if "." in k]
	for k in compose_op:
		atomic_op.remove(k)
	return sorted(atomic_op), sorted(compose_op)

def get_opening_op(compose_op, reverse):
	opening_op = {}
	for key in compose_op:
		part = key.split('.')
		opening_op[part[0]] = [part[1], reverse[key]]
	return opening_op

def get_first(iter):
	return [k[0] for k in iter]

def get_begin_op(atomic_op, opening_op):
	begin_op = []
	begin_op.extend(get_first(atomic_op))
	begin_op.extend(get_first(opening_op))
	return sorted(set(begin_op))

def get_begin_opening_op(opening_op):
	return sorted(get_first(opening_op))

def get_maxlen(iter):
	return max([len(k) for k in iter])

def get_escape(grammar):
	if 'ESCAPE' in grammar:
		return grammar['ESCAPE'][0]
	return ''


class Grammar(object):
	def __init__(self, path):
		self.grammar = get_grammar_from_path(path)
		self.grammar['NEW_LINE'] = '\n'
		self.reverse = get_reverse_grammar(self.grammar)
		self.escape = get_escape(self.grammar)

		self.atomic_op, self.compose_op = get_atomic_compose_op(self.reverse.keys())
		if '\\' in self.atomic_op:
			self.atomic_op.remove('\\')
		self.opening_op = get_opening_op(self.compose_op, self.reverse)

		self.begin_op = get_begin_op(self.atomic_op, self.opening_op)
		self.begin_opening_op = get_begin_opening_op(self.opening_op)

		self.maxlen_opening_op = get_maxlen(self.opening_op)
		self.maxlen_atomic_op = get_maxlen(self.atomic_op)


def get_grammar(path):
	return Grammar(path)
