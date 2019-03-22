#!/usr/bin/env python3

from pprint import pprint
import utils.file as fl
from collections import deque as dq


def get_grammar(path):
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
