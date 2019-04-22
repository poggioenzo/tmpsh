#!/usr/bin/env python3

from pprint import pprint
import utils.file as fl
import utils.strcontain as sc
#
# import file as fl
# import strcontain as sc

class Grammar(object):
	def __init__(self, path):
		self.path = path
		self.get_grammar_from_path() # self.grammar
		self.get_reverse_grammar() # self.reverse

	def get_grammar_from_path(self):
		text = fl.get_text(self.path)
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
		self.grammar = grammar

	def get_reverse_grammar(self):
		reverse_grammar = {}
		for key in self.grammar:
			for value in self.grammar[key]:
				reverse_grammar[value] = key
		self.reverse = reverse_grammar


	def add_symbol(self, symbol, symbol_name):
		if symbol_name not in self.grammar:
			self.grammar[symbol_name] = []
		self.grammar[symbol_name].append(symbol)
		if symbol not in self.reverse:
			self.reverse[symbol] = {}
		self.reverse[symbol]= symbol_name


	def __str__(self):
		attrs = vars(self)
		nv = sorted([item for item in attrs.items()])
		for n, v in nv:
			print(n + ':')
			pprint(v)
		return '.'

class ShellGrammar(Grammar):
	"""docstring for ."""
	def __init__(self, path='grammar.txt'):
		super().__init__(path)
		self.add_symbol('\n', 'NEW_LINE')
		self.spaces = [' ', '\t']
		self.get_leaf_op()
		self.get_escape()
		if 'ESCAPE' in self.grammar:
			self.leaf_op.remove(self.grammar['ESCAPE'][0])
		self.maxlen_leaf_op = self.get_maxlen(self.leaf_op)
		self.get_opening_tags()

	def get_escape(self):
		if 'ESCAPE' in self.grammar:
			self.escape = self.grammar['ESCAPE'][0]
		else:
			self.escape = ''

	def get_list_op(self, func):
		return [key for key in self.reverse if not func(key)]

	def get_leaf_op(self):
		self.leaf_op = self.get_list_op(sc.containalphanum)

	def get_maxlen(self,iter):
		return max([len(k) for k in iter])

	def get_first(self,iter):
		return [k[0] for k in iter]

	def get_opening_tags(self):
		self.opening_tags = {}
		if 'SUB_PROCESS' in self.grammar and 'QUOTES' in self.grammar:
			opening_tags = self.grammar['SUB_PROCESS']
			opening_tags.extend(self.grammar['QUOTES'])
			for tag in opening_tags:
				tag_split = tag.split()
				tag_op = tag_split[0]
				tag_end =tag_split[-1]
				self.opening_tags[tag_op] = tag_end



if __name__ == '__main__':
	a = ShellGrammar()
	print(a)
	# print(a.grammar['CMDAND'])
	# print(a.grammar['NEW_LINE'])
