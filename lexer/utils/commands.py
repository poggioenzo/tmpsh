#!/usr/bin/env python3

import utils.tokenizer as tk
import utils.readgrammar as rd
global GRAMMAR
GRAMMAR = rd.get_grammar('grammar.txt')


class Commands(object):
	def __init__(self, term_inputs):
		self.term_inputs = term_inputs
		self.tokens = []
		tk.tokenize(term_inputs, GRAMMAR, self.tokens)
		self.commands = []
