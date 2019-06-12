#!/usr/bin/env python3

import unittest
from utils.tagstokens import TagsTokens


class TestTags(unittest.TestCase):

    def test_tags_001(self):
        tokens = ['ls', ' ', '-l', '\n']
        tags = TagsTokens(tokens).get_tags().tags
        self.assertEqual(['STMT', 'SPACES', 'STMT', 'NEW_LINE'], tags)

    def test_tags_002(self):
        tokens = ['echo', ' ', '"', 'qwert', '"', '"',
                  'yuiop', '"']
        tags = TagsTokens(tokens).get_tags().tags
        self.assertEqual(
            ['STMT', 'SPACES', 'DQUOTES', 'STMT', 'END_DQUOTES', 'DQUOTES',
             'STMT', 'END_DQUOTES'], tags)

    def test_tags_003(self):
        tokens = ['VAR', ' ', '+=', ' ', '0', '\n']
        tags = TagsTokens(tokens).get_tags().tags
        self.assertEqual(['STMT', 'SPACES', 'CONCATENATION',
                          'SPACES', 'STMT', 'NEW_LINE'], tags)

    def test_tags_004(self):
        tokens = ['ls', ' ', '-l', ' ', '\\\n/',
                  ' ', ';', '\n']
        tags = TagsTokens(tokens).get_tags().tags
        self.assertEqual(['STMT', 'SPACES', 'STMT', 'SPACES',
                          'STMT', 'SPACES', 'END_COMMAND', 'NEW_LINE'], tags)

    def test_tags_005(self):
        tokens = ['echo', ' ', '1', '&&', '\n',
                  '<(', 'LOL', ')', '||', '\n',
                  'LOL', '\n']
        tags = TagsTokens(tokens).get_tags().tags
        self.assertEqual(
            ['STMT', 'SPACES', 'STMT', 'CMDAND', 'NEW_LINE',
             'CMDSUBST3', 'STMT', 'END_BRACKET', 'CMDOR', 'NEW_LINE', 'STMT',
             'NEW_LINE'], tags)

    def test_tags_006(self):
        tokens = ['echo', ' ', '${', 'var', '}', '_', '$var',
                  '${', 'var2', '}', '_']
        tags = TagsTokens(tokens).get_tags().tags
        self.assertEqual(['STMT', 'SPACES', 'BRACEPARAM', 'STMT', 'END_BRACE',
                          'STMT', 'STMT', 'BRACEPARAM', 'STMT', 'END_BRACE',
                          'STMT'], tags)

    def test_tags_007(self):
        tokens = ['echo', ' ', 'text', '>>',
                  'file', ' ', '>>', ' ', 'file2', '\n']
        tags = TagsTokens(tokens).get_tags().tags
        self.assertEqual(['STMT', 'SPACES', 'STMT', 'APPEND',
                          'STMT', 'SPACES', 'APPEND', 'SPACES', 'STMT',
                          'NEW_LINE'], tags)

    def test_tags_008(self):
        tokens = ['>(', '<(', 'echo', ' ', 'test',
                  ' ', '>', ' ', 'file.txt', ')', ')', ' ',
                  '&&', ' \t\t', '$VAR_TEST', '|', ' ',
                  'cat', ' ', '<<', ' ', 'HERE', '\n',
                  'testHERE', '\n', 'HERE']
        tags = TagsTokens(tokens).get_tags().tags
        self.assertEqual(
            ['CMDSUBST2', 'CMDSUBST3', 'STMT', 'SPACES', 'STMT',
             'SPACES', 'TRUNC', 'SPACES', 'STMT', 'END_BRACKET',
             'END_BRACKET', 'SPACES', 'CMDAND', 'SPACES', 'STMT',
             'PIPE', 'SPACES', 'STMT', 'SPACES', 'HEREDOC', 'SPACES',
             'STMT', 'NEW_LINE', 'STMT', 'NEW_LINE', 'STMT'], tags)


class TestTagsDoubleQuotes(unittest.TestCase):

    def test_tags_double_quotes_double_quotes_000(self):
        term_inputs = '"{CMD}"'
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['DQUOTES', 'STMT', 'STMT',
                          'STMT', 'END_DQUOTES'], tags)

    def test_tags_double_quotes_001(self):
        term_inputs = '"(CMD)"'
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['DQUOTES', 'STMT', 'STMT',
                          'STMT', 'END_DQUOTES'], tags)

    def test_tags_double_quotes_002(self):
        term_inputs = '">(CMD)"'
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['DQUOTES', 'STMT', 'STMT',
                          'STMT', 'END_DQUOTES'], tags)

    def test_tags_double_quotes_003(self):
        term_inputs = '"<(CMD)"'
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['DQUOTES', 'STMT', 'STMT',
                          'STMT', 'END_DQUOTES'], tags)

    def test_tags_double_quotes_004(self):
        term_inputs = '"$(CMD)"'
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['DQUOTES', 'CMDSUBST1', 'STMT',
                          'END_BRACKET', 'END_DQUOTES'], tags)

    def test_tags_double_quotes_005(self):
        term_inputs = '"${CMD}"'
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['DQUOTES', 'BRACEPARAM', 'STMT',
                          'END_BRACE', 'END_DQUOTES'], tags)

    def test_tags_double_quotes_006(self):
        term_inputs = '""CMD""'
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['DQUOTES', 'END_DQUOTES', 'STMT',
                          'DQUOTES', 'END_DQUOTES'], tags)

    def test_tags_double_quotes_007(self):
        term_inputs = '"\'$(CMD;CMD|CMD)\'"'
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['DQUOTES', 'STMT', 'CMDSUBST1', 'STMT',
                          'END_COMMAND', 'STMT', 'PIPE', 'STMT',
                          'END_BRACKET', 'STMT', 'END_DQUOTES'], tags)

    def test_tags_double_quotes_008(self):
        term_inputs = '"\'CMD\'"'
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['DQUOTES', 'STMT', 'STMT',
                          'STMT', 'END_DQUOTES'], tags)

    def test_tags_double_quotes_009(self):
        term_inputs = '"$(" \'$(CMD)\' ")"'
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(
            ['DQUOTES', 'CMDSUBST1', 'DQUOTES', 'SPACES', 'STMT', 'CMDSUBST1',
             'STMT', 'END_BRACKET', 'STMT', 'SPACES', 'END_DQUOTES',
             'END_BRACKET', 'END_DQUOTES'], tags)

    def test_tags_double_quotes_010(self):
        term_inputs = '"$("CMD")"'
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['DQUOTES', 'CMDSUBST1', 'DQUOTES',
                          'STMT', 'END_DQUOTES', 'END_BRACKET',
                          'END_DQUOTES'], tags)

    def test_tags_double_quotes_011(self):
        term_inputs = '" CMD  CMD "'
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['DQUOTES', 'SPACES', 'STMT', 'SPACES',
                          'STMT', 'SPACES', 'END_DQUOTES'], tags)

    def test_tags_double_quotes_012(self):
        term_inputs = '"$(")")"'
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['DQUOTES', 'CMDSUBST1', 'DQUOTES', 'STMT',
                          'END_DQUOTES', 'END_BRACKET', 'END_DQUOTES'], tags)

    def test_tags_double_quotes_013(self):
        term_inputs = '"$("$(")"'
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['DQUOTES', 'CMDSUBST1', 'DQUOTES', 'CMDSUBST1',
                          'DQUOTES', 'STMT', 'END_DQUOTES'], tags)


class TestTagsQuotes(unittest.TestCase):

    def test_tags_quotes_000(self):
        term_inputs = "'{cmd}'"
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['QUOTE', 'STMT', 'STMT',
                          'STMT', 'END_QUOTE'], tags)

    def test_tags_quotes_001(self):
        term_inputs = "'${cmd}'"
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['QUOTE', 'STMT', 'STMT',
                          'STMT', 'END_QUOTE'], tags)

    def test_tags_quotes_002(self):
        term_inputs = "'$(CMD)'"
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['QUOTE', 'STMT', 'STMT',
                          'STMT', 'END_QUOTE'], tags)

    def test_tags_quotes_003(self):
        term_inputs = "'(CMD)'"
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['QUOTE', 'STMT', 'STMT',
                          'STMT', 'END_QUOTE'], tags)

    def test_tags_quotes_004(self):
        term_inputs = "'>(CMD)'"
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['QUOTE', 'STMT', 'STMT',
                          'STMT', 'END_QUOTE'], tags)

    def test_tags_quotes_005(self):
        term_inputs = "'<(CMD)'"
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['QUOTE', 'STMT', 'STMT',
                          'STMT', 'END_QUOTE'], tags)

    def test_tags_quotes_006(self):
        term_inputs = "'\"CMD\"'"
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['QUOTE', 'STMT', 'STMT',
                          'STMT', 'END_QUOTE'], tags)

    def test_tags_quotes_007(self):
        term_inputs = "''CMD''"
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['QUOTE', 'END_QUOTE', 'STMT',
                          'QUOTE', 'END_QUOTE'], tags)

    def test_tags_quotes_008(self):
        term_inputs = "''$(CMD)''"
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['QUOTE', 'END_QUOTE', 'CMDSUBST1', 'STMT',
                          'END_BRACKET', 'QUOTE', 'END_QUOTE'], tags)

    def test_tags_quotes_009(self):
        term_inputs = "''${CMD}''"
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['QUOTE', 'END_QUOTE', 'BRACEPARAM', 'STMT',
                          'END_BRACE', 'QUOTE', 'END_QUOTE'], tags)

    def test_tags_quotes_010(self):
        term_inputs = "'\"$(CMD)\"'"
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['QUOTE', 'STMT', 'STMT', 'STMT', 'STMT',
                          'STMT', 'END_QUOTE'], tags)

    def test_tags_quotes_011(self):
        term_inputs = "'\"${CMD}\"'"
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['QUOTE', 'STMT', 'STMT', 'STMT', 'STMT',
                          'STMT', 'END_QUOTE'], tags)

    def test_tags_quotes_012(self):
        term_inputs = "'\" ${ CMD CMD }\"'"
        tags = TagsTokens().init_with_input(term_inputs).tags
        self.assertEqual(['QUOTE', 'STMT', 'SPACES', 'STMT', 'SPACES', 'STMT',
                          'SPACES', 'STMT', 'SPACES', 'STMT', 'STMT',
                          'END_QUOTE'], tags)


if __name__ == '__main__':
    unittest.main()
