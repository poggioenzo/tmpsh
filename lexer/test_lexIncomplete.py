#!/usr/bin/env python3

import unittest
from utils.commands import ListCommands

class testLexIncomplete(unittest.TestCase):

    def testLexIncompleter001(self):
        term_inputs = 'cmd &&'
        listc = ListCommands(term_inputs)
        self.assertTrue(listc.valid)
        self.assertTrue(listc.incomplete)
        self.assertListEqual(['CMDAND', '>'], listc.to_complete)


if __name__ == '__main__':
    unittest.main()
