#!/usr/bin/env python3

import utils.tokenizer as tk
from utils.readgrammar import ShellGrammar
import utils.strcontain as sc
global GRAMMAR
GRAMMAR = ShellGrammar()

class Cmd(object):
	def __init__(self, start, tags, ends=[]):
		self.start = start
		self.end = start #
		self.sub = [] # list de cmd
		self.tagsubtitution = []
		self.get_end(start, tags[start:])
		self.input_buffer = tags[self.start: self.end]
		self.ends = GRAMMAR.grammar['TERMINATOR']
		if ends != []:
			self.ends = ends
		self.syntax_ok = False


	def get_end(self, start, tags):
		i = 0
		len_tags = len(tags)
		while i < len_tags:
			if tags[i] in self.ends:
				break
			i += 1
		i += 1
		self.end = self.start + i

	def reduce_shift(self):
		self.stack = []
		i = 0
		len_input_buffer = len(self.input_buffer)
		while (i < len_input_buffer):
			tag = self.tags[i]
			if tag == 'SPACES':
				pass
			elif ():
			i += 1




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
