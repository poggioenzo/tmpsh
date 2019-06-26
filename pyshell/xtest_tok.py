#!/usr/bin/env python3

import unittest
import utils.tokenizer as tk


class TestTokenisation(unittest.TestCase):

    def test_tok_001(self):
        soluce = ['ls', ' ', '-l', '\n']
        command = ''.join(soluce)
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, soluce)

    def test_tok_002(self):
        soluce = ['ls', ' ', '-l', ' ', '\n']
        command = ''.join(soluce)
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, soluce)

    def test_tok_003(self):
        soluce = ['  ', 'ls', ' ', '-l', ' ', '/', ';',
                  '        ', '\n']
        command = ''.join(soluce)
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, soluce)

    def test_tok_004(self):
        soluce = ['ls', ' ', '-l', ' ', '\\\n/',
                  ' ', ';', '\n']
        command = ''.join(soluce)
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, soluce)

    def test_tok_005(self):
        soluce = ['ls', ' ', '-l', ' ', '\\ /', ';', '\n']
        command = ''.join(soluce)
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, soluce)

    def test_tok_006(self):
        soluce = ['echo', ' ', '\\$PATH', ' ', '||', ' ', 'echo',
                  ' ', '$path', '\n']
        command = ''.join(soluce)
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, soluce)

    def test_tok_007(self):
        soluce = ['echo', ' ', '"', '\n', 'ewline',
                  '\n', 'ewline', '"', '\n']
        command = ''.join(soluce)
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, soluce)

    def test_tok_008(self):
        soluce = ['echo', ' ', '$(', ' ', 'echo',
                  ' ', '(', '1', ' ', '&&', ' ', '0', ')',
                                      ')', '\n']
        command = ''.join(soluce)
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, soluce)

    def test_tok_009(self):
        soluce = ['echo', ' ', '1', '&&', '\n',
                  '<(', 'LOL', ')', '||', '\n',
                  'LOL', '\n']
        command = ''.join(soluce)
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, soluce)

    def test_tok_010(self):
        soluce = [' ', '<(', 'LOL', ')', '\n', '"', ' ',
                  'LOL', ' ', '"', '\n', '>(', '   ',
                  'LOL',
                  ')', '\n', "'", 'LOL', '    ', "'", '\n',
                  '$(', ' ', 'LOL', ')', '\n', '${', ' ',
                  'LOL', '}', '\n', '{', 'LOL', '}', '\n',
                  '(', 'LOL', ')', '\n']
        command = ''.join(soluce)
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, soluce)

    def test_tok_011(self):
        soluce = ['echo', ' ', '"', '\\"', '"', ' ', '&',
                  ';', ' ', '$(', 'echo', ' ', '-n', ' ',
                  '1', ')', '||',
                  '${', 'echo', '\n', '-n', ' ', '1', '}',
                  ';', ' ', '2', '>&', '-', ' ', '>>',
                  'file', ' ', '>>', ' ', 'file2', '\n']
        command = ''.join(soluce)
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, soluce)

    def test_tok_012(self):
        soluce = ['echo', ' ', '"', '\\"', '"',
                  ' ', '&', '\n']
        command = ''.join(soluce)
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, soluce)

    def test_tok_013(self):
        soluce = ['echo', ' ', 'text', '>>',
                  'file', ' ', '>>', ' ', 'file2', '\n']
        command = ''.join(soluce)
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, soluce)

    def test_tok_014(self):
        soluce = ['echo', ' ', 'text', '||',
                  'file', ' ', '<<', ' ', 'file2', '\n']
        command = ''.join(soluce)
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, soluce)

    def test_tok_015(self):
        soluce = ['echo', ' ', '\\f\\i\\l\\e', '\n', 'VAR',
                  ' ', '=', ' ', '0', '\n', 'VAR', '=',
                  '1', '\n', 'VAR', ' ', '+=', '1', '\n',
                  'echo', ' ', '"', '\\$VAR', ' ', '\\=',
                  ' ', '$VAR', '"', '\n']
        command = ''.join(soluce)
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, soluce)

    def test_tok_016(self):
        soluce = ['echo', ' ', '\\f\\i\\l\\e', '\n']
        command = ''.join(soluce)
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, soluce)

    def test_tok_017(self):
        soluce = ['VAR', ' ', '=', ' ', '0', '\n',
                  'VAR', '=', '1', '\n', 'VAR', ' ',
                  '+=', '1', '\n']
        command = ''.join(soluce)
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, soluce)

    def test_tok_018(self):
        soluce = ['VAR', ' ', '=', ' ', '0', '\n']
        command = ''.join(soluce)
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, soluce)

    def test_tok_019(self):
        soluce = ['VAR', ' ', '+=', ' ', '0', '\n']
        command = ''.join(soluce)
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, soluce)


class TestTokenisation2(unittest.TestCase):

    def test_tok_001(self):
        command = "&&||+==&\\"
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['&&', '||', '+=', '=', '&', '\\'])

    def test_tok_002(self):
        command = '1 && 0 || $PATH += "~/tmpsh/bin"; $VAR=0 &\necho LOL'
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['1', ' ', '&&', ' ', '0', ' ', '||', ' ',
                                      '$PATH', ' ', '+=', ' ',
                                      '"', '~/tmpsh/bin', '"', ';', ' ',
                                      '$VAR', '=', '0', ' ', '&', '\n',
                                      'echo', ' ', 'LOL'])

    def test_tok_003(self):
        command = '''>(<(echo test > file.txt)) && 		$VAR_TEST| cat'''
        command += ' << HERE\ntestHERE\nHERE'''
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['>(', '<(', 'echo', ' ', 'test',
                                      ' ', '>', ' ', 'file.txt', ')', ')', ' ',
                                      '&&', ' \t\t', '$VAR_TEST', '|', ' ',
                                      'cat', ' ', '<<', ' ', 'HERE', '\n',
                                      'testHERE', '\n', 'HERE'])

    def test_tok_004(self):
        command = '                 \\\necho \\\\test             '
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['                 ', '\\\necho',
                                      ' ', '\\\\test', '             '])

    def test_tok_005(self):
        command = ' $({ () lol'
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, [' ', '$(', '{', ' ', '(', ')',
                                      ' ', 'lol'])

    def test_tok_006(self):
        command = 'echo "qwert""yuiop"'
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['echo', ' ', '"', 'qwert', '"', '"',
                                      'yuiop', '"'])

    def test_tok_007(self):
        command = 'echo "qwert"\'yuiop\''
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['echo', ' ', '"', 'qwert', '"', "'",
                                      'yuiop', "'"])

    def test_tok_008(self):
        command = 'echo ${var}_$var${var2}_'
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(
            tokens, ['echo', ' ', '${', 'var', '}', '_', '$var',
                     '${', 'var2', '}', '_'])

    def test_tok_009(self):
        command = 'echo "yolo"&&ls'
        tokens = []
        tk.tokenize(command, tokens)
        self.assertListEqual(tokens, ['echo', ' ', '"', 'yolo',
                                      '"', '&&', 'ls'])


if __name__ == '__main__':
    unittest.main()
