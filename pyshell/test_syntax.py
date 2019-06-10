#!/usr/bin/env python3

import unittest
from utils.tagstokens import TagsTokens


class TestSyntaxValid(unittest.TestCase):

    def test_syntax_valid_000(self):
        tokens = ['  ', 'ls', ' ', '-l', ' ', '/', ';', '        ', '\n']
        tagstokens = TagsTokens(tokens).get_tags().check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)

    def test_syntax_valid_001(self):
        tokens = ['ls', ' ', '-l', ' ', '\\\n/', ' ', ';', '\n']
        tagstokens = TagsTokens(tokens).get_tags().check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)

    def test_syntax_valid_002(self):
        tokens = ['echo', ' ', '\\$PATH', ' ',
                  '||', ' ', 'echo', ' ', '$path', '\n']
        tagstokens = TagsTokens(tokens).get_tags().check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)

    def test_syntax_valid_003(self):
        tokens = ['echo', ' ', '"', '\n', 'ewline', '\n', 'ewline', '"', '\n']
        tagstokens = TagsTokens(tokens).get_tags().check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)

    def test_syntax_valid_004(self):
        tokens = ['echo', ' ', '"', '\\"', '"', ' ', '&', '\n']
        tagstokens = TagsTokens(tokens).get_tags().check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)

    def test_syntax_valid_005(self):
        tokens = ['echo', ' ', 'text', '>>',
                  'file', ' ', '>>', ' ', 'file2', '\n']
        tagstokens = TagsTokens(tokens).get_tags().check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)

    def test_syntax_valid_006(self):
        tokens = ['echo', ' ', 'text', '||',
                  'file', ' ', '<<', ' ', 'file2', '\n']
        tagstokens = TagsTokens(tokens).get_tags().check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)

    def test_syntax_valid_007(self):
        tokens = ['                 ', '\\\necho',
                  ' ', '\\\\test', '             ']
        tagstokens = TagsTokens(tokens).get_tags().check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)

    def test_syntax_valid_008(self):
        tokens = [' ', '$(', '{', ' ', '(', 'lol', ')', ' ', 'lol']
        tagstokens = TagsTokens(tokens).get_tags().check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)

    def test_syntax_valid_009(self):
        tokens = ['echo', ' ', '"', 'qwert', '"', '"', 'yuiop', '"']
        tagstokens = TagsTokens(tokens).get_tags().check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)

    def test_syntax_valid_010(self):
        tokens = ['echo', ' ', '"', 'qwert', '"', "'", 'yuiop', "'"]
        tagstokens = TagsTokens(tokens).get_tags().check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)

    def test_syntax_valid_011(self):
        tokens = ['echo', ' ', '${', 'var', '}',
                  '_', '$var', '${', 'var2', '}', '_']
        tagstokens = TagsTokens(tokens).get_tags().check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)

    def test_syntax_valid_012(self):
        tokens = ['echo', ' ', '"', 'yolo', '"', '&&', 'ls']
        tagstokens = TagsTokens(tokens).get_tags().check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)

    def test_syntax_valid_013(self):
        tokens = ['echo', ' ', '\\', ' ']
        tagstokens = TagsTokens(tokens).get_tags().check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)

    def test_syntax_valid_014(self):
        terminput = '$(")(")'
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)

    def test_syntax_valid_015(self):
        tokens = ['']
        tagstokens = TagsTokens(tokens).get_tags().check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)

    def test_syntax_valid_016(self):
        tokens = ['\n']
        tagstokens = TagsTokens(tokens).get_tags().check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)


class TestSyntaxError(unittest.TestCase):

    def test_syntax_error_001(self):
        terminput = 'echo }'
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(tagstokens.valid)
        self.assertEqual(tagstokens.token_error, '}')

    def test_syntax_error_002(self):
        terminput = ')'
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(tagstokens.valid)
        self.assertEqual(tagstokens.token_error, ')')

    def test_syntax_error_003(self):
        terminput = '${ &&'
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(tagstokens.valid)
        self.assertEqual(tagstokens.token_error, '&&')

    def test_syntax_error_004(self):
        terminput = ' \' \' ||  &&'
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(tagstokens.valid)
        self.assertEqual(tagstokens.token_error, '&&')

    def test_syntax_error_005(self):
        terminput = ' >() '
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(tagstokens.valid)
        self.assertEqual(tagstokens.token_error, ')')

    def test_syntax_error_006(self):
        terminput = ' <() '
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(tagstokens.valid)
        self.assertEqual(tagstokens.token_error, ')')

    def test_syntax_error_007(self):
        terminput = ' >() '
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(tagstokens.valid)
        self.assertEqual(tagstokens.token_error, ')')

    def test_syntax_error_008(self):
        terminput = ' {} '
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(not tagstokens.valid)
        self.assertEqual(tagstokens.token_error, '')  # '}')

    def test_syntax_error_009(self):
        terminput = ' ${} '
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(not tagstokens.valid)
        self.assertEqual(tagstokens.token_error, '')  # '}')

    def test_syntax_error_010(self):
        terminput = ' $() '
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(not tagstokens.valid)
        self.assertEqual(tagstokens.token_error, '')  # ')')

    def test_syntax_error_011(self):
        terminput = ' (   \t   ) '
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(tagstokens.valid)
        self.assertEqual(tagstokens.token_error, ')')

    def test_syntax_error_012(self):
        terminput = ' = $PATH'
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(tagstokens.valid)
        self.assertEqual(tagstokens.token_error, '=')

    def test_syntax_error_013(self):
        terminput = ' += $PATH'
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(tagstokens.valid)
        self.assertEqual(tagstokens.token_error, '+=')

    def test_syntax_error_014(self):
        terminput = ';'  # ZSHLIKE
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(not tagstokens.valid)
        self.assertEqual(tagstokens.token_error, '')

    def test_syntax_error_015(self):
        terminput = 'ls ; ;'  # ZSHLIKE
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(not tagstokens.valid)
        self.assertEqual(tagstokens.token_error, '')

    def test_syntax_error_016(self):
        terminput = 'ls ;;'  # beacause ;; have a true meanning
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(tagstokens.valid)
        self.assertEqual(tagstokens.token_error, ';;')

    def test_syntax_error_017(self):
        terminput = ' ; ;'  # ZSHLIKE
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(not tagstokens.valid)
        self.assertEqual(tagstokens.token_error, '')

    def test_syntax_error_018(self):
        terminput = ' & ;'
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(tagstokens.valid)
        self.assertEqual(tagstokens.token_error, '&')

    def test_syntax_error_019(self):
        terminput = ' | ls '
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(tagstokens.valid)
        self.assertEqual(tagstokens.token_error, '|')

    def test_syntax_error_020(self):
        terminput = ' $( } '
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(tagstokens.valid)
        self.assertEqual(tagstokens.token_error, '}')


class TestSyntaxError2(unittest.TestCase):

    def test_syntax_error_001(self):
        terminput = 'echo lol >    '
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(tagstokens.valid)
        self.assertEqual(tagstokens.token_error, '>')

    def test_syntax_error_002(self):
        terminput = ' >&'
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(tagstokens.valid)
        self.assertEqual(tagstokens.token_error, '>&')

    def test_syntax_error_003(self):
        terminput = '(>&)'
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(tagstokens.valid)
        self.assertEqual(tagstokens.token_error, ')')

    def test_syntax_error_004(self):
        terminput = ' >> >>'
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(tagstokens.valid)
        self.assertEqual(tagstokens.token_error, '>>')

    def test_syntax_error_005(self):
        terminput = ' \\>> '
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertFalse(tagstokens.valid)
        self.assertEqual(tagstokens.token_error, '>')


class TestSyntaxIncomplete(unittest.TestCase):

    def test_syntax_incomplete_001(self):
        terminput = '$('
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)
        self.assertTrue(tagstokens.incomplete)
        self.assertEqual(tagstokens.token_error, '')
        self.assertEqual(tagstokens.stack, ['CMDSUBST1'])

    def test_syntax_incomplete_002(self):
        terminput = '$(${'
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)
        self.assertTrue(tagstokens.incomplete)
        self.assertEqual(tagstokens.token_error, '')
        self.assertEqual(tagstokens.stack, ['CMDSUBST1', 'BRACEPARAM'])

    def test_syntax_incomplete_003(self):
        terminput = '$(${"}"'
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)
        self.assertTrue(tagstokens.incomplete)
        self.assertEqual(tagstokens.token_error, '')
        self.assertEqual(tagstokens.stack, ['CMDSUBST1', 'BRACEPARAM'])

    def test_syntax_incomplete_004(self):
        terminput = '$(${"}"(\') $( ${ ('
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)
        self.assertTrue(tagstokens.incomplete)
        self.assertEqual(tagstokens.token_error, '')
        self.assertEqual(tagstokens.stack, [
                         'CMDSUBST1', 'BRACEPARAM', 'SUBSH', 'QUOTE'])

    def test_syntax_incomplete_005(self):
        terminput = '$(${"}"(\') $( ${ (\' \''
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)
        self.assertTrue(tagstokens.incomplete)
        self.assertEqual(tagstokens.token_error, '')
        self.assertEqual(tagstokens.stack, [
                         'CMDSUBST1', 'BRACEPARAM', 'SUBSH', 'QUOTE'])

    def test_syntax_incomplete_006(self):
        terminput = 'ls && '
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)
        self.assertTrue(tagstokens.incomplete)
        self.assertEqual(tagstokens.token_error, '')
        self.assertEqual(tagstokens.stack, ['CMDAND'])

    def test_syntax_incomplete_007(self):
        terminput = '$(ls || '
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)
        self.assertTrue(tagstokens.incomplete)
        self.assertEqual(tagstokens.token_error, '')
        self.assertEqual(tagstokens.stack, ['CMDSUBST1', 'CMDOR'])

    def test_syntax_incomplete_008(self):
        terminput = '" " "\' '
        tagstokens = TagsTokens().init_with_input(terminput).check_syntax()
        print(tagstokens)
        self.assertTrue(tagstokens.valid)
        self.assertTrue(tagstokens.incomplete)
        self.assertEqual(tagstokens.token_error, '')
        self.assertEqual(tagstokens.stack, ['DQUOTES'])


if __name__ == '__main__':
    unittest.main()
