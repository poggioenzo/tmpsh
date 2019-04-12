#!/usr/bin/env python3

from utils.readgrammar import ShellGrammar
global GRAMMAR
GRAMMAR = ShellGrammar()

def split_commands(tokens):
	len_tokens = len(tokens)
	i = 0
	commands = []
	command = []
	while i < len_tokens:
