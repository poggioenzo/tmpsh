#!/usr/bin/env python3

import unittest
from utils.tagstokens import TagsTokens


class TestTags(unittest.TestCase):

    def test_tags_001(self):
        term_inputs = '&&'
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['CMDAND'], tags)

    def test_tags_002(self):
        term_inputs = "'$(ls)'"
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['QUOTES', 'STMT', 'STMT', 'STMT', 'QUOTES'], tags)

    def test_tags_003(self):
        term_inputs = "'$(ls)'"
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['QUOTES', 'STMT', 'STMT', 'STMT', 'QUOTES'], tags)

    def test_tags_004(self):
        term_inputs = "'${PATH}'"
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['QUOTES', 'STMT', 'STMT', 'STMT', 'QUOTES'], tags)

    def test_tags_005(self):
        term_inputs = '"${PATH}"'
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['DQUOTES', 'BRACEPARAM', 'STMT',
                          'END_BRACE', 'DQUOTES'], tags)

    def test_tags_006(self):
        term_inputs = "'$(echo ls)'"
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(
            ['QUOTES', 'STMT', 'STMT', 'SPACES', 'STMT', 'STMT', 'QUOTES'],
            tags)

    def test_tags_007(self):
        term_inputs = '"$(echo ls)"'
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['DQUOTES', 'CMDSUBST1', 'STMT', 'SPACES', 'STMT',
                          'END_BRACKET', 'DQUOTES'], tags)


if __name__ == '__main__':
    unittest.main()
