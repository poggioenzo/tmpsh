#!/usr/bin/env python3

import utils.tokenizer as tk
from utils.readgrammar import ShellGrammar
import utils.strcontain as sc
global GRAMMAR
GRAMMAR = ShellGrammar()

class Cmd(object):
	def __init__(self, start, tags, ends=[]):
		self.start = start
		self.end = start
		self.ends = GRAMMAR.grammar['TERMINATOR']
		if ends != []:
			self.ends = ends
		self.sub = [] # list de cmd
		self.get_end(tags)
		if ends != []:
			self.start -= 1
		self.tags = tags[self.start: self.end]
		self.syntax_ok = False
		self.reduce_shift()

	def get_end(self, tags):
		i = self.start
		len_tags = len(tags)
		while i < len_tags:
			curr_tag = tags[i]
			if curr_tag in self.ends:
				break
			elif curr_tag in GRAMMAR.opening_tags:
				i += 1
				subcmd = Cmd(i, tags, [GRAMMAR.opening_tags[curr_tag]])
				i = subcmd.end
				self.sub.append(subcmd)
			else:
				i += 1
		i += 1
		if i > len_tags:
			i = len_tags
		self.end = i

	def reduce(self):
		len_stack = len(self.stack)
		i = 0
		while i < len_stack:
			key = ' '.join(self.stack[i-len_stack:])
			if key in GRAMMAR.reverse:
				self.stack[i-len_stack:] = self.stack[:i-len_stack - 1] + [GRAMMAR.reverse[key]]
				self.reduce()
				len_stack = len(self.stack)
			i += 1
		return (0)

	def reduce_shift(self):
		self.stack = []
		i = 0
		len_tags = len(self.tags)
		copy = self.tags.copy()
		while (i < len_tags):
			tag = self.tags[i]
			if tag == 'SPACES':
				copy.pop(0)
			elif self.reduce():
				pass
			elif copy != []: #shift
				self.stack.append(copy.pop(0))
			else:
				break
			i += 1
		self.reduce()
		print(self.stack)



class ListCommands(object):
	def __init__(self, term_inputs):
		self.term_inputs = term_inputs
		self.tokens = []
		tk.tokenize(term_inputs, self.tokens)
		self.get_tags()
		self.get_tree_commands()

	def get_tags(self):
		tags = []
		for tok in self.tokens:
			if tok in GRAMMAR.leaf_op:
				tags.append(GRAMMAR.reverse[tok])
			elif sc.containspaces(tok):
				tags.append('SPACES')
			else:
				tags.append('STMT')
		self.tags = tags

	def get_tree_commands(self):
		tags = self.tags
		tree_commands = []
		i = 0
		len_tags = len(tags)
		while i < len_tags:
			cmd = Cmd(i, tags)
			i = cmd.end
			tree_commands.append(cmd)
		self.tree_commands = tree_commands
