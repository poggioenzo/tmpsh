#!/usr/bin/env python3

import unittest
from utils.tagstokens import TagsTokens


class TestSyntaxSubsh(unittest.TestCase):

    def test_subsh_001(self):
        term_input = '()'
        tt = TagsTokens().init_with_input(term_input).check_syntax()
        print(tt)
        self.assertEqual(['SUBSH', 'END_BRACKET'], tt.tags)
        self.assertEqual(['(', ')'], tt.tokens)
        self.assertEqual(['SUBSH', 'END_BRACKET'], tt.stack)
        self.assertFalse(tt.valid)
        self.assertFalse(tt.incomplete)

    def test_subsh_002(self):
        term_input = '( )'
        tt = TagsTokens().init_with_input(term_input).check_syntax()
        print(tt)
        self.assertEqual(['SUBSH', 'SPACES', 'END_BRACKET'], tt.tags)
        self.assertEqual(['(', ' ', ')'], tt.tokens)
        self.assertEqual(['SUBSH', 'END_BRACKET'], tt.stack)
        self.assertFalse(tt.valid)
        self.assertFalse(tt.incomplete)

    def test_subsh_003(self):
        term_input = '(cmd) cmd'
        tt = TagsTokens().init_with_input(term_input).check_syntax()
        print(tt)
        self.assertEqual(
            ['SUBSH', 'STMT', 'END_BRACKET', 'SPACES', 'STMT'], tt.tags)
        self.assertEqual(['(', 'cmd', ')', ' ', 'cmd'], tt.tokens)
        self.assertEqual([], tt.stack)
        self.assertFalse(tt.valid)
        self.assertFalse(tt.incomplete)

    def test_subsh_004(self):
        term_input = 'cmd&&(cmd); cmd'
        tt = TagsTokens().init_with_input(term_input).check_syntax()
        print(tt)
        self.assertEqual(
            ['STMT', 'CMDAND', 'SUBSH', 'STMT', 'END_BRACKET', 'END_COMMAND', 'SPACES',
             'STMT'], tt.tags)
        self.assertEqual(['cmd', '&&', '(', 'cmd', ')',
                          ';', ' ', 'cmd'], tt.tokens)
        self.assertEqual([], tt.stack)
        self.assertFalse(tt.valid)
        self.assertFalse(tt.incomplete)


if __name__ == '__main__':
    unittest.main()
