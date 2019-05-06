#!/usr/bin/env python3

import unittest
from utils.commands import ListCommands

class testLexOk(unittest.TestCase):

    def testLexOk001(self):
        term_inputs = ''
        listc = ListCommands(term_inputs)
        self.assertTrue(listc.valid)

    def testLexOk002(self):
        term_inputs = 'cmd'
        listc = ListCommands(term_inputs)
        self.assertTrue(listc.valid)

    def testLexOk003(self):
        term_inputs = ' cmd cmd cmd       cmd cmd          cmd      cmd       '
        listc = ListCommands(term_inputs)
        self.assertTrue(listc.valid)

    def testLexOk004(self):
        term_inputs = ' cmd ; cmd cmd & cmd \n cmd ;'
        listc = ListCommands(term_inputs)
        self.assertTrue(listc.valid)

    def testLexOk005(self):
        term_inputs = ' cmd || cmd && cmd | cmd '
        listc = ListCommands(term_inputs)
        self.assertTrue(listc.valid)

    def testLexOk006(self):
        term_inputs = ' >> cmd; >&-; >cmd    ; <cmd ; << EOF '
        listc = ListCommands(term_inputs)
        self.assertTrue(listc.valid)

    def testLexOk007(self):
        term_inputs = ' $() '
        listc = ListCommands(term_inputs)
        self.assertTrue(listc.valid)

    def testLexOk008(self):
        term_inputs = ' ($(${ { \' \' " " } })) '
        listc = ListCommands(term_inputs)
        self.assertTrue(listc.valid)

    def testLexOk009(self):
        term_inputs = '(cmd ; $( cmd && ${ cmd { \' \' || " $PATH " \\} } }))'
        listc = ListCommands(term_inputs)
        self.assertTrue(listc.valid)

    def testLexOk010(self):
        term_inputs = '$PATH = ; $PATH += $FOO'
        listc = ListCommands(term_inputs)
        self.assertTrue(listc.valid)

if __name__ == '__main__':
    unittest.main()
