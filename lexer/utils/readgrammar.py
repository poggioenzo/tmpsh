#!/usr/bin/env python3

from pprint import pprint
import utils.file as fl
import utils.strcontain as sc

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
		self.reverse[symbol].append(symbol_name)


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
		self.grammar['NEW_LINE'] = ['\n']
		self.reverse['\n'] = 'NEW_LINE'
		#self.atomic_op = [], self.compose_op = [], self.leaf_op = []
		self.get_atomic_compose_leaf_op()
		self.get_escape()
		if 'ESCAPE' in self.grammar:
			self.atomic_op.remove(self.grammar['ESCAPE'][0])
			self.leaf_op.remove(self.grammar['ESCAPE'][0])
		self.quotes = []
		if 'QUOTES' in self.grammar:
			for k in self.grammar['QUOTES']:
				self.quotes.append(self.grammar[k][0].split('.')[0])
		#self.opening_op()
		self.get_opening_op()
		self.get_begin_op()

		self.maxlen_opening_op = self.get_maxlen(self.opening_op)
		self.maxlen_atomic_op = self.get_maxlen(self.atomic_op)
		self.maxlen_leaf_op = self.get_maxlen(self.leaf_op)

	def get_escape(self):
		if 'ESCAPE' in self.grammar:
			self.escape = self.grammar['ESCAPE'][0]
		else:
			self.escape = ''

	def get_list_op(self, func):
		return [key for key in self.reverse if not func(key)]

	def get_atomic_compose_leaf_op(self):
		self.atomic_op = self.get_list_op(sc.containalphanum)
		self.compose_op = [k for k in self.atomic_op if "." in k]
		self.leaf_op = self.atomic_op.copy()
		for k in self.compose_op:
			self.atomic_op.remove(k)
			self.leaf_op.extend(k.split('.'))
			self.leaf_op.remove(k)
		self.leaf_op = sorted(set(self.leaf_op))

	def get_opening_op(self):
		self.opening_op = {}
		for key in self.compose_op:
			part = key.split('.')
			self.opening_op[part[0]] = [part[1], self.reverse[key]]

	def get_begin_op(self):
		self.begin_op = []
		self.begin_op.extend(self.get_first(self.atomic_op))
		self.begin_opening_op = self.get_first(self.opening_op)
		self.begin_op.extend(self.begin_opening_op)
		self.begin_op = sorted(set(self.begin_op))
		self.begin_opening_op = sorted(set(self.begin_opening_op))

	def get_maxlen(self,iter):
		return max([len(k) for k in iter])

	def get_first(self,iter):
		return [k[0] for k in iter]


if __name__ == '__main__':
	a = ShellGrammar()
	print(a)
	print(a.grammar['CMDAND'])
	print(a.grammar['NEW_LINE'])
