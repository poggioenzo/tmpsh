#!/usr/bin/env python3

import unittest
from utils.commands import ListCommands


class TestLexIncomplete(unittest.TestCase):

    def testLexIncompleter001(self):
        term_inputs = 'cmd &&'
        listc = ListCommands(term_inputs)
        self.assertTrue(listc.valid)
        self.assertTrue(listc.incomplete)
        self.assertListEqual(['CMDAND', '>'], listc.to_complete)

    def testLexIncompleter002(self):
        term_inputs = '$( cmd ) &&  '
        listc = ListCommands(term_inputs)
        self.assertTrue(listc.valid)
        self.assertTrue(listc.incomplete)
        self.assertListEqual(['CMDAND', '>'], listc.to_complete)

    def testLexIncompleter003(self):
        term_inputs = '$( cmd  &&   '
        listc = ListCommands(term_inputs)
        self.assertTrue(listc.valid)
        self.assertTrue(listc.incomplete)
        self.assertListEqual(['CMDSUBST1', 'CMDAND', '>'], listc.to_complete)

    def testLexIncompleter004(self):
        term_inputs = '"'
        listc = ListCommands(term_inputs)
        self.assertTrue(listc.valid)
        self.assertTrue(listc.incomplete)
        self.assertListEqual(['DQUOTES', '>'], listc.to_complete)

    def testLexIncompleter005(self):
        term_inputs = '" ""'
        listc = ListCommands(term_inputs)
        self.assertTrue(listc.valid)
        self.assertTrue(listc.incomplete)
        self.assertListEqual(['DQUOTES', '>'], listc.to_complete)

    def testLexIncompleter006(self):
        term_inputs = '" \\"""'
        listc = ListCommands(term_inputs)
        self.assertTrue(listc.valid)
        self.assertTrue(listc.incomplete)
        self.assertListEqual(['DQUOTES', '>'], listc.to_complete)

    def testLexIncompleter007(self):
        term_inputs = '\''
        listc = ListCommands(term_inputs)
        self.assertTrue(listc.valid)
        self.assertTrue(listc.incomplete)
        self.assertListEqual(['QUOTE', '>'], listc.to_complete)

    def testLexIncompleter008(self):
        term_inputs = 'ls -l \\'
        listc = ListCommands(term_inputs)
        self.assertTrue(listc.valid)
        self.assertTrue(listc.incomplete)
        self.assertListEqual(['>'], listc.to_complete)

    def testLexIncompleter009(self):
        term_inputs = '\\'
        listc = ListCommands(term_inputs)
        self.assertTrue(listc.valid)
        self.assertTrue(listc.incomplete)
        self.assertListEqual(['>'], listc.to_complete)

    def testLexIncompleter010(self):
        term_inputs = '${ $( 	{ ( ( ) >( <(  '
        listc = ListCommands(term_inputs)
        self.assertTrue(listc.valid)
        self.assertTrue(listc.incomplete)
        self.assertListEqual(['BRACEPARAM', 'CMDSUBST1', 'CURSH', 'SUBSH',
                              'CMDSUBST2', 'CMDSUBST3', '>'],
                             listc.to_complete)

    def testLexIncompleter011(self):
        term_inputs = "' $("
        listc = ListCommands(term_inputs)
        self.assertTrue(listc.valid)
        self.assertTrue(listc.incomplete)
        self.assertListEqual(['QUOTE', '>'],
                             listc.to_complete)


if __name__ == '__main__':
    unittest.main()
