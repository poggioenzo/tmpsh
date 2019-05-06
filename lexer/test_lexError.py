#!/usr/bin/env python3

import unittest
from utils.commands import ListCommands

class testLexError(unittest.TestCase):

    def testLexError001(self):
        term_inputs = '&&'
        listc = ListCommands(term_inputs)
        self.assertFalse(listc.valid)
        self.assertIs('&&', listc.error)

if __name__ == '__main__':
    unittest.main()
