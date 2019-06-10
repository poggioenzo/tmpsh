#!/usr/bin/env python3

import unittest
from utils.commands import ListCommands


class TestSyntaxValid(unittest.TestCase):

    def test_syntax_valid_001(self):
        term_inputs = ''


class TestSyntaxError(unittest.TestCase):

    def test_syntax_error_001(self):
        term_inputs = '&&'
        listc = ListCommands(term_inputs)
        self.assertFalse(listc.valid)
        self.assertIs('&&', listc.error)


class TestSyntaxIncomplete(unittest.TestCase):

    def test_syntax_incomplete_001(self):
        term_inputs = '&&'
        listc = ListCommands(term_inputs)
        self.assertFalse(listc.valid)
        self.assertIs('&&', listc.error)


if __name__ == '__main__':
    unittest.main()
