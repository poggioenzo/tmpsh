#!/usr/bin/env python3

import unittest
import utils.tokenizer as tk
import utils.file as fl


class TestTokenisation(unittest.TestCase):

    def test_tok_00(self):
        command = fl.get_text('unittest/tok/0')
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['ls', ' ', '-l', '\n'])

    def test_tok_00_1(self):
        command = fl.get_text('unittest/tok/0_1')
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['ls', ' ', '-l', ' ', '\n'])

    def test_tok_01(self):
        command = fl.get_text('unittest/tok/1')
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['  ', 'ls', ' ', '-l', ' ', '/', ';',
                                      '        ', '\n'])

    def test_tok_02(self):
        command = fl.get_text('unittest/tok/2')
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['ls', ' ', '-l', ' ', '\\\n/',
                                      ' ', ';', '\n'])

    def test_tok_03(self):
        command = fl.get_text('unittest/tok/3')
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['ls', ' ', '-l', ' ', '\\ /', ';', '\n'])

    def test_tok_04(self):
        command = fl.get_text('unittest/tok/4')
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(
            tokens, ['echo', ' ', '\\$PATH', ' ', '||', ' ', 'echo',
                     ' ', '$path', '\n'])

    def test_tok_05(self):
        command = fl.get_text('unittest/tok/5')
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['echo', ' ', '"', '\n', 'ewline',
                                      '\n', 'ewline', '"', '\n'])

    def test_tok_06(self):
        command = fl.get_text('unittest/tok/6')
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['echo', ' ', '$(', ' ', 'echo',
                                      ' ', '(', '1', ' ', '&&', ' ', '0', ')',
                                      ')', '\n'])

    def test_tok_07(self):
        command = fl.get_text('unittest/tok/7')
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['echo', ' ', '1', '&&', '\n',
                                      '<(', 'LOL', ')', '||', '\n',
                                      'LOL', '\n'])

    def test_tok_07_1(self):
        command = fl.get_text('unittest/tok/7_1')
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, [' ', '<(', 'LOL', ')', '\n', '"', ' ',
                                      'LOL', ' ', '"', '\n', '>(', '   ',
                                      'LOL',
                                      ')', '\n', "'", 'LOL', '    ', "'", '\n',
                                      '$(', ' ', 'LOL', ')', '\n', '${', ' ',
                                      'LOL', '}', '\n', '{', 'LOL', '}', '\n',
                                      '(', 'LOL', ')', '\n'])

    def test_tok_08(self):
        command = fl.get_text('unittest/tok/8')
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['echo', ' ', '"', '\\"', '"', ' ', '&',
                                      ';', ' ', '$(', 'echo', ' ', '-n', ' ',
                                      '1', ')', '||',
                                      '${', 'echo', '\n', '-n', ' ', '1', '}',
                                      ';', ' ', '2', '>&', '-', ' ', '>>',
                                      'file', ' ', '>>', ' ', 'file2', '\n'])

    def test_tok_08_1(self):
        command = fl.get_text('unittest/tok/8_1')
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['echo', ' ', '"', '\\"', '"',
                                      ' ', '&', '\n'])

    def test_tok_08_2(self):
        command = fl.get_text('unittest/tok/8_2')
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['echo', ' ', 'text', '>>',
                                      'file', ' ', '>>', ' ', 'file2', '\n'])

    def test_tok_08_3(self):
        command = fl.get_text('unittest/tok/8_3')
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['echo', ' ', 'text', '||',
                                      'file', ' ', '<<', ' ', 'file2', '\n'])

    def test_tok_09(self):
        command = fl.get_text('unittest/tok/9')
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['echo', ' ', '\\f\\i\\l\\e', '\n', 'VAR',
                                      ' ', '=', ' ', '0', '\n', 'VAR', '=',
                                      '1', '\n', 'VAR', ' ', '+=', '1', '\n',
                                      'echo', ' ', '"', '\\$VAR', ' ', '\\=',
                                      ' ', '$VAR', '"', '\n'])

    def test_tok_09_1(self):
        command = fl.get_text('unittest/tok/9_1')
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['echo', ' ', '\\f\\i\\l\\e', '\n'])

    def test_tok_09_2(self):
        command = fl.get_text('unittest/tok/9_2')
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['VAR', ' ', '=', ' ', '0', '\n',
                                      'VAR', '=', '1', '\n', 'VAR', ' ',
                                      '+=', '1', '\n'])

    def test_tok_09_3(self):
        command = fl.get_text('unittest/tok/9_3')
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['VAR', ' ', '=', ' ', '0', '\n'])

    def test_tok_09_4(self):
        command = fl.get_text('unittest/tok/9_4')
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['VAR', ' ', '+=', ' ', '0', '\n'])


class TestTokenisation2(unittest.TestCase):

    def test_tok_10(self):
        command = "&&||+==&\\"
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['&&', '||', '+=', '=', '&', '\\'])

    def test_tok_11(self):
        command = '1 && 0 || $PATH += "~/tmpsh/bin"; $VAR=0 &\necho LOL'
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['1', ' ', '&&', ' ', '0', ' ', '||', ' ',
                                      '$PATH', ' ', '+=', ' ',
                                      '"', '~/tmpsh/bin', '"', ';', ' ',
                                      '$VAR', '=', '0', ' ', '&', '\n',
                                      'echo', ' ', 'LOL'])

    def test_tok_12(self):
        command = '''>(<(echo test > file.txt)) && 		$VAR_TEST| cat'''
        command += ' << HERE\ntestHERE\nHERE'''
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['>(', '<(', 'echo', ' ', 'test',
                                      ' ', '>', ' ', 'file.txt', ')', ')', ' ',
                                      '&&', ' \t\t', '$VAR_TEST', '|', ' ',
                                      'cat', ' ', '<<', ' ', 'HERE', '\n',
                                      'testHERE', '\n', 'HERE'])

    def test_tok_13(self):
        command = '                 \\\necho \\\\test             '
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['                 ', '\\\necho',
                                      ' ', '\\\\test', '             '])

    def test_tok_14(self):
        command = ' $({ () lol'
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, [' ', '$(', '{', ' ', '(', ')',
                                      ' ', 'lol'])

    def test_tok_15(self):
        command = 'echo "qwert""yuiop"'
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['echo', ' ', '"', 'qwert', '"', '"',
                                      'yuiop', '"'])

    def test_tok_16(self):
        command = 'echo "qwert"\'yuiop\''
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['echo', ' ', '"', 'qwert', '"', "'",
                                      'yuiop', "'"])

    def test_tok_17(self):
        command = 'echo ${var}_$var${var2}_'
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(
            tokens, ['echo', ' ', '${', 'var', '}', '_', '$var',
                     '${', 'var2', '}', '_'])

    def test_tok_18(self):
        command = 'echo "yolo"&&ls'
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['echo', ' ', '"', 'yolo',
                                      '"', '&&', 'ls'])


if __name__ == '__main__':
    unittest.main()
