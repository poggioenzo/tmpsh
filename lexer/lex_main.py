#!/usr/bin/env python3

import utils.readgrammar as rd
import utils.tokenizer as tk
from utils.commands import Commands


global GRAMMAR
GRAMMAR = rd.get_grammar('grammar.txt')


def shift(arg):
	pass

def reduce(arg):
	pass

def check(arg):
	pass

def split_cmd(tokens):
	pass


def lexer(tokens, objectif):
	reverse = rd.get_reverse_grammar(GRAMMAR)
	stack = []
	# while stack != objectif:
	# 	['B', 'C', 'D']
	print(reverse)


if __name__ == '__main__':
	a=Commands("ls -l")
