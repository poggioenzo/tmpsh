#!/usr/bin/env python3

from pprint import pprint
import utils.file as fl


def get_grammar(path):
	text = fl.get_text(path)
	lines = text.split('\n')
	length = len(lines)
	i = 0
	grammar = {}
	while (i < length):
		if (len(lines[i]) > 0 and lines[i][0] != '\n' and lines[i][0] != '\t' and lines[i][0] != '#'):
			keyword = lines[i][:-1]
			i += 1
			if keyword not in grammar:
				grammar[keyword] = []
			while (1):
				if len(lines[i]) > 0 and lines[i][0] == '\t':
					grammar[keyword].append(lines[i][1:])
				else:
					break
				i += 1
		i += 1
	return grammar
