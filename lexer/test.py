#!/usr/bin/env python3


import utils.readgrammar as rg
import utils.tokenizer as tk
import utils.file as fl
import sys
import os
import unittest


class TestTok(unittest.TestCase):

	def testTok0(self):
		grammar = rg.get_grammar("grammar.txt")
		command = fl.get_text('test/0')
		tokens = []
		tk.tokenize(command, grammar, tokens)
		self.assertListEqual(tokens, ['ls', '-l', '\n'])

	def testTok0_1(self):
		grammar = rg.get_grammar("grammar.txt")
		command = fl.get_text('test/0_1')
		tokens = []
		tk.tokenize(command, grammar, tokens)
		self.assertListEqual(tokens, ['ls', '-l', '\n'])

	def testTok1(self):
		grammar = rg.get_grammar("grammar.txt")
		command = fl.get_text('test/1')
		tokens = []
		tk.tokenize(command, grammar, tokens)
		self.assertListEqual(tokens, ['ls', '-l', '/', ';', '\n'])

	def testTok2(self):
		grammar = rg.get_grammar("grammar.txt")
		command = fl.get_text('test/2')
		tokens = []
		tk.tokenize(command, grammar, tokens)
		self.assertListEqual(tokens, ['ls', '-l', '\n/', ';', '\n'])

	def testTok3(self):
		grammar = rg.get_grammar("grammar.txt")
		command = fl.get_text('test/3')
		tokens = []
		tk.tokenize(command, grammar, tokens)
		self.assertListEqual(tokens, ['ls', '-l', ' /', ';', '\n'])

	def testTok4(self):
		 grammar = rg.get_grammar("grammar.txt")
		 command = fl.get_text('test/4')
		 tokens = []
		 tk.tokenize(command, grammar, tokens)
		 self.assertListEqual(
			 tokens, ['echo', '$PATH', '||', 'echo', '$path', '\n'])

	def testTok5(self):
		grammar = rg.get_grammar("grammar.txt")
		command = fl.get_text('test/5')
		tokens = []
		tk.tokenize(command, grammar, tokens)
		self.assertListEqual(tokens, ['echo', '"\newline\newline"', '\n'])

	def testTok6(self):
		grammar = rg.get_grammar("grammar.txt")
		command = fl.get_text('test/6')
		tokens = []
		tk.tokenize(command, grammar, tokens)
		self.assertListEqual(tokens, ['echo', '$( echo (1 && 0))', '\n'])

	def testTok7(self):
		grammar = rg.get_grammar("grammar.txt")
		command = fl.get_text('test/7')
		tokens = []
		tk.tokenize(command, grammar, tokens)
		self.assertListEqual(tokens, ['echo', '1', '&&', '\n',
									  '<(LOL)', '||', '\n', 'LOL', '\n'])

	def testTok7_1(self):
		grammar = rg.get_grammar("grammar.txt")
		command = fl.get_text('test/7_1')
		tokens = []
		tk.tokenize(command, grammar, tokens)
		self.assertListEqual(tokens, ['<(LOL)', '\n', '" LOL "', '\n', '>(   LOL)', '\n', "'LOL    '", '\n', '$( LOL)', '\n', '${ LOL}', '\n', '{LOL}', '\n', '(LOL)', '\n'])


	def testTok8(self):
		 grammar = rg.get_grammar("grammar.txt")
		 command = fl.get_text('test/8')
		 tokens = []
		 tk.tokenize(command, grammar, tokens)
		 self.assertListEqual(tokens, ['echo', '"\\""', '&', ';', '$(echo -n 1)',
									   '||', '${echo\n-n 1}', ';', '2',
									   '>&', '-', '>>', 'file', '>>',
									   'file2', '\n'])
	def testTok8_1(self):
		 grammar = rg.get_grammar("grammar.txt")
		 command = fl.get_text('test/8_1')
		 tokens = []
		 tk.tokenize(command, grammar, tokens)
		 self.assertListEqual(tokens, ['echo', '"\\""','&', "\n"])

	def testTok8_2(self):
		 grammar = rg.get_grammar("grammar.txt")
		 command = fl.get_text('test/8_2')
		 tokens = []
		 tk.tokenize(command, grammar, tokens)
		 self.assertListEqual(tokens, ['echo', 'text','>>', 'file', '>>', 'file2', "\n"])



	# def testTok9(self):
	# 	 grammar = rg.get_grammar("grammar.txt")
	# 	 command = fl.get_text('test/9')
	# 	 tokens = []
	# 	 tk.tokenize(command, grammar, tokens)
	# 	 self.assertListEqual(tokens, ['echo', 'file', '\n', 'VAR', '=', '0', '\n',
	# 								   'VAR', '=', '1', '\n', 'VAR', '+=', '1', '\n',
	# 								   '"\$VAR \= $VAR"', '\n'])


if __name__ == '__main__':
	unittest.main()
