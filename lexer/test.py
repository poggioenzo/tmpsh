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
		command = fl.get_text('unittest/0')
		tokens = []
		tk.tokenize(command, grammar, tokens)
		self.assertListEqual(tokens, ['ls', '-l', '\n'])

	def testTok0_1(self):
		grammar = rg.get_grammar("grammar.txt")
		command = fl.get_text('unittest/0_1')
		tokens = []
		tk.tokenize(command, grammar, tokens)
		self.assertListEqual(tokens, ['ls', '-l', '\n'])

	def testTok1(self):
		grammar = rg.get_grammar("grammar.txt")
		command = fl.get_text('unittest/1')
		tokens = []
		tk.tokenize(command, grammar, tokens)
		self.assertListEqual(tokens, ['ls', '-l', '/', ';', '\n'])

	def testTok2(self):
		grammar = rg.get_grammar("grammar.txt")
		command = fl.get_text('unittest/2')
		tokens = []
		tk.tokenize(command, grammar, tokens)
		self.assertListEqual(tokens, ['ls', '-l', '\n/', ';', '\n'])

	def testTok3(self):
		grammar = rg.get_grammar("grammar.txt")
		command = fl.get_text('unittest/3')
		tokens = []
		tk.tokenize(command, grammar, tokens)
		self.assertListEqual(tokens, ['ls', '-l', ' /', ';', '\n'])

	def testTok4(self):
		 grammar = rg.get_grammar("grammar.txt")
		 command = fl.get_text('unittest/4')
		 tokens = []
		 tk.tokenize(command, grammar, tokens)
		 self.assertListEqual(
			 tokens, ['echo', '$PATH', '||', 'echo', '$path', '\n'])

	def testTok5(self):
		grammar = rg.get_grammar("grammar.txt")
		command = fl.get_text('unittest/5')
		tokens = []
		tk.tokenize(command, grammar, tokens)
		self.assertListEqual(tokens, ['echo', '"\newline\newline"', '\n'])

	def testTok6(self):
		grammar = rg.get_grammar("grammar.txt")
		command = fl.get_text('unittest/6')
		tokens = []
		tk.tokenize(command, grammar, tokens)
		self.assertListEqual(tokens, ['echo', '$( echo (1 && 0))', '\n'])

	def testTok7(self):
		grammar = rg.get_grammar("grammar.txt")
		command = fl.get_text('unittest/7')
		tokens = []
		tk.tokenize(command, grammar, tokens)
		self.assertListEqual(tokens, ['echo', '1', '&&', '\n',
									  '<(LOL)', '||', '\n', 'LOL', '\n'])

	def testTok7_1(self):
		grammar = rg.get_grammar("grammar.txt")
		command = fl.get_text('unittest/7_1')
		tokens = []
		tk.tokenize(command, grammar, tokens)
		self.assertListEqual(tokens, ['<(LOL)', '\n', '" LOL "', '\n',
										'>(   LOL)', '\n', "'LOL    '",
										'\n', '$( LOL)', '\n', '${ LOL}',
										 '\n', '{LOL}', '\n', '(LOL)', '\n'])


	def testTok8(self):
		 grammar = rg.get_grammar("grammar.txt")
		 command = fl.get_text('unittest/8')
		 tokens = []
		 tk.tokenize(command, grammar, tokens)
		 self.assertListEqual(tokens, ['echo', '"\\""', '&', ';', '$(echo -n 1)',
									   '||', '${echo\n-n 1}', ';', '2',
									   '>&', '-', '>>', 'file', '>>',
									   'file2', '\n'])
	def testTok8_1(self):
		 grammar = rg.get_grammar("grammar.txt")
		 command = fl.get_text('unittest/8_1')
		 tokens = []
		 tk.tokenize(command, grammar, tokens)
		 self.assertListEqual(tokens, ['echo', '"\\""','&', "\n"])

	def testTok8_2(self):
		 grammar = rg.get_grammar("grammar.txt")
		 command = fl.get_text('unittest/8_2')
		 tokens = []
		 tk.tokenize(command, grammar, tokens)
		 self.assertListEqual(tokens, ['echo', 'text','>>', 'file', '>>',
		  								'file2', "\n"])

	def testTok8_3(self):
		 grammar = rg.get_grammar("grammar.txt")
		 command = fl.get_text('unittest/8_3')
		 tokens = []
		 tk.tokenize(command, grammar, tokens)
		 self.assertListEqual(tokens, ['echo', 'text','||', 'file', '<<',
		  								'file2', "\n"])



	def testTok9(self):
		 grammar = rg.get_grammar("grammar.txt")
		 command = fl.get_text('unittest/9')
		 tokens = []
		 tk.tokenize(command, grammar, tokens)
		 self.assertListEqual(tokens, ['echo', 'file', '\n', 'VAR', '=', '0', '\n',
									   'VAR', '=', '1', '\n', 'VAR', '+=', '1', '\n',
									   'echo','"\$VAR \= $VAR"', '\n'])

	def testTok9_1(self):
		 grammar = rg.get_grammar("grammar.txt")
		 command = fl.get_text('unittest/9_1')
		 tokens = []
		 tk.tokenize(command, grammar, tokens)
		 self.assertListEqual(tokens, ['echo', 'file', '\n'])


	def testTok9_2(self):
		 grammar = rg.get_grammar("grammar.txt")
		 command = fl.get_text('unittest/9_2')
		 tokens = []
		 tk.tokenize(command, grammar, tokens)
		 self.assertListEqual(tokens, [ 'VAR', '=', '0', '\n',
									   'VAR', '=', '1', '\n',
									   'VAR', '+=', '1', '\n'])

	def testTok9_3(self):
		 grammar = rg.get_grammar("grammar.txt")
		 command = fl.get_text('unittest/9_3')
		 tokens = []
		 tk.tokenize(command, grammar, tokens)
		 self.assertListEqual(tokens, [ 'VAR', '=', '0', '\n'])

	def testTok9_4(self):
		 grammar = rg.get_grammar("grammar.txt")
		 command = fl.get_text('unittest/9_4')
		 tokens = []
		 tk.tokenize(command, grammar, tokens)
		 self.assertListEqual(tokens, [ 'VAR', '+=', '0', '\n'])

	def testTok10(self):
		 grammar = rg.get_grammar("grammar.txt")
		 command = "&&||+==&\\"
		 tokens = []
		 tk.tokenize(command, grammar, tokens)
		 self.assertListEqual(tokens, [ '&&', '||', '+=', '=', '&'])

	def testTok11(self):
		 grammar = rg.get_grammar("grammar.txt")
		 command = '1 && 0 || $PATH += "~/tmpsh/bin"; $VAR=0 &\\\necho LOL'
		 tokens = []
		 tk.tokenize(command, grammar, tokens)
		 self.assertListEqual(tokens, ['1', '&&', '0', '||', '$PATH', '+=',
		 								'"~/tmpsh/bin"',';', '$VAR','=','0', '&', '\necho', 'LOL'])

	def testTok12(self):
		 grammar = rg.get_grammar("grammar.txt")
		 command = '>(<(echo test > file.txt)) && 		$VAR_TEST| cat << HERE\ntestHERE\nHERE'
		 tokens = []
		 tk.tokenize(command, grammar, tokens)
		 self.assertListEqual(tokens, ['>(<(echo test > file.txt))', '&&', '$VAR_TEST', '|', 'cat', '<<', 'HERE', '\n','testHERE', '\n','HERE'])

	def testTok13(self):
		 grammar = rg.get_grammar("grammar.txt")
		 command = '                \\\necho \\\\test             '
		 tokens = []
		 tk.tokenize(command, grammar, tokens)
		 self.assertListEqual(tokens, ['\necho', '\\test',])

	def testTok14(self):
		 grammar = rg.get_grammar("grammar.txt")
		 command = ' $({ () lol'
		 tokens = []
		 tk.tokenize(command, grammar, tokens)
		 self.assertListEqual(tokens, ['$({ () lol'])



if __name__ == '__main__':
	unittest.main()
