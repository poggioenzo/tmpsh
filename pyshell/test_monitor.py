import unittest
from utils.tagstokens import TagsTokens


class TestMonitor(unittest.TestCase):

    def test_tags_001(self):
        term_input = ''
        tt = TagsTokens().init_with_input(term_input).check_syntax()
        tags = tt.tags
        self.assertEqual([], tags)
