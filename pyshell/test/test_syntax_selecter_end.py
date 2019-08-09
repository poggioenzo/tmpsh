#!/usr/bin/env python3

import unittest
from utils.tagstokens import TagsTokens


class TestSyntaxSelecterEndInvalid(unittest.TestCase):

    def test_selecter_end_001(self):
        term_input = ';;'
        tt = TagsTokens().init_with_input(term_input).check_syntax()
        print(tt)
        self.assertEqual(['SELECTER_END'], tt.tags)
        self.assertEqual([';;'], tt.tokens)
        self.assertEqual(['SELECTER_END'], tt.stack)
        self.assertFalse(tt.valid)
        self.assertFalse(tt.incomplete)

    def test_selecter_end_002(self):
        term_input = 'cmd;;'
        tt = TagsTokens().init_with_input(term_input).check_syntax()
        print(tt)
        self.assertEqual(['STMT', 'SELECTER_END'], tt.tags)
        self.assertEqual(['cmd', ';;'], tt.tokens)
        self.assertEqual(['SELECTER_END'], tt.stack)
        self.assertFalse(tt.valid)
        self.assertFalse(tt.incomplete)


if __name__ == '__main__':
    unittest.main()
