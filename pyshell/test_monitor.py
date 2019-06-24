import unittest
from utils.tagstokens import TagsTokens


class TestMonitorBasicValid(unittest.TestCase):

    def test_basic_valid_001(self):
        """Basic test no input -> no tags no tokens."""
        term_input = ''
        tt = TagsTokens().init_with_input(term_input).check_syntax()
        print(tt)
        self.assertEqual([], tt.tags)
        self.assertEqual([], tt.tokens)
        self.assertEqual([], tt.stack)
        self.assertTrue(tt.valid)
        self.assertFalse(tt.incomplete)

    def test_basic_valid_002(self):
        """Just one command."""
        term_input = 'cmd'
        tt = TagsTokens().init_with_input(term_input).check_syntax()
        print(tt)
        self.assertEqual(['STMT'], tt.tags)
        self.assertEqual(['cmd'], tt.tokens)
        self.assertEqual([], tt.stack)
        self.assertTrue(tt.valid)
        self.assertFalse(tt.incomplete)

    def test_basic_valid_003(self):
        """Just one command with lots spaces around=. Test srip methode."""
        term_input = '       cmd                 '
        tt = TagsTokens().init_with_input(term_input).check_syntax()
        print(tt)
        self.assertEqual(['STMT'], tt.tags)
        self.assertEqual(['cmd'], tt.tokens)
        self.assertEqual([], tt.stack)
        self.assertTrue(tt.valid)
        self.assertFalse(tt.incomplete)

    def test_basic_valid_004(self):
        """Test command with terminator."""
        term_input = 'cmd;'
        tt = TagsTokens().init_with_input(term_input).check_syntax()
        print(tt)
        self.assertEqual(['STMT', 'END_COMMAND'], tt.tags)
        self.assertEqual(['cmd', ';'], tt.tokens)
        self.assertEqual([], tt.stack)
        self.assertTrue(tt.valid)
        self.assertFalse(tt.incomplete)

    def test_basic_valid_005(self):
        """Test terminator alone."""
        term_input = ';'
        tt = TagsTokens().init_with_input(term_input).check_syntax()
        print(tt)
        self.assertEqual(['END_COMMAND'], tt.tags)
        self.assertEqual([';'], tt.tokens)
        self.assertEqual([], tt.stack)
        self.assertTrue(tt.valid)
        self.assertFalse(tt.incomplete)

    def test_basic_valid_006(self):
        """Test newline in raw input."""
        term_input = '\n'
        tt = TagsTokens().init_with_input(term_input).check_syntax()
        print(tt)
        self.assertEqual([], tt.tags)
        self.assertEqual([], tt.tokens)
        self.assertEqual([], tt.stack)
        self.assertTrue(tt.valid)
        self.assertFalse(tt.incomplete)

    def test_basic_valid_007(self):
        """Test newline in raw input."""
        tokens = ['\n']
        tt = TagsTokens(tokens).get_tags().check_syntax()
        print(tt)
        self.assertEqual(['NEW_LINE'], tt.tags)
        # self.assertEqual(['\n'], tt.tokens)
        self.assertEqual([], tt.stack)
        self.assertTrue(tt.valid)
        self.assertFalse(tt.incomplete)

    def test_basic_valid_008(self):
        """Test BACKGROUND_JOBS and spacing in token input."""
        tokens = ['  ', 'cmd', ' \t', '&', ' \t']
        tt = TagsTokens(tokens).get_tags().check_syntax()
        print(tt)
        self.assertEqual(['STMT', 'SPACES', 'BACKGROUND_JOBS'], tt.tags)
        self.assertEqual(['cmd', ' \t', '&'], tt.tokens)
        self.assertEqual([], tt.stack)
        self.assertTrue(tt.valid)
        self.assertFalse(tt.incomplete)


class TestMonitorBasicInvalid(unittest.TestCase):

    def test_basic_invalid_001(self):
        """Test terminator alone."""
        term_input = '&'
        tt = TagsTokens().init_with_input(term_input).check_syntax()
        print(tt)
        self.assertEqual(['BACKGROUND_JOBS'], tt.tags)
        self.assertEqual(['&'], tt.tokens)
        self.assertEqual(['BACKGROUND_JOBS'], tt.stack)
        self.assertFalse(tt.valid)
        self.assertFalse(tt.incomplete)
