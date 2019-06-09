#!/usr/bin/env python3

import unittest
import utils.shift_reduce as sr
from utils.grammar import Grammar
GRAMMAR = Grammar("grammar/grammar_test.txt")


class TestShiftReduce(unittest.TestCase):

    def test_shift_reduce_001(self):
        entry = ''.split()
        exepted_output = []
        self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

    def test_shift_reduce_002(self):
        entry = 'A'.split()
        exepted_output = ['A']
        self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

    def test_shift_reduce_003(self):
        entry = 'A B'.split()
        exepted_output = ['A']
        self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

    def test_shift_reduce_004(self):
        entry = 'A C C C'.split()
        exepted_output = ['A']
        self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

    def test_shift_reduce_005(self):
        entry = 'A B C C C'.split()
        exepted_output = ['A']
        self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

    def test_shift_reduce_006(self):
        entry = 'A A'.split()
        exepted_output = ['A']
        self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

    def test_shift_reduce_007(self):
        entry = 'A A A'.split()
        exepted_output = ['A']
        self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

    def test_shift_reduce_008(self):
        entry = 'B'.split()
        exepted_output = ['A']
        self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

    def test_shift_reduce_009(self):
        entry = 'C C C'.split()
        exepted_output = ['A']
        self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

    def test_shift_reduce_010(self):
        entry = 'D D D D D D'.split()
        exepted_output = ['A']
        self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

    def test_shift_reduce_011(self):
        entry = 'C A'.split()
        exepted_output = ['C', 'A']
        self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

    def test_shift_reduce_012(self):
        entry = 'C B'.split()
        exepted_output = ['C', 'A']
        self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

    def test_shift_reduce_013(self):
        entry = 'E B'.split()
        exepted_output = ['D', 'A']
        self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

    def test_shift_reduce_014(self):
        entry = 'E B E'.split()
        exepted_output = ['D', 'A', 'D']
        self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

    def test_shift_reduce_015(self):
        entry = 'C C D D C C E E'.split()
        exepted_output = ['A']
        self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

    def test_shift_reduce_016(self):
        entry = 'C C D D C C E E'.split()
        exepted_output = ['A']
        self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

    def test_shift_reduce_017(self):
        entry = 'A B C D E'.split()
        exepted_output = ['A', 'C', 'C']
        self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

    def test_shift_reduce_018(self):
        entry = 'B C E C'.split()
        exepted_output = ['A', 'C', 'D', 'C']
        self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)


class TestShiftReduceHard(unittest.TestCase):

    def test_shift_reduce_hard_019(self):
        entry = 'E E E D A A E E A B A A'.split()
        exepted_output = ['C', 'C', 'A', 'C', 'A']
        self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

    def test_shift_reduce_hard_020(self):
        entry = ('B D B E B B C C C E B D E E A A B A'
                 + ' A B D E C E E B D C D D B B E D D C').split()
        exepted_output = ['A', 'D', 'A', 'D', 'A', 'D', 'A', 'C', 'D',
                          'A', 'D', 'C', 'C', 'A', 'C', 'D', 'C']
        self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

    def test_shift_reduce_hard_021(self):
        entry = ('SPACES D SPACES E SPACES SPACES SPACES E SPACES D SPACES A D'
                 + ' SPACES E SPACES SPACES SPACES').split()
        exepted_output = ['C', 'C', 'A', 'C']
        self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

    def test_shift_reduce_hard_022(self):
        entry = 'A B C E C'.split()
        exepted_output = ['A', 'C', 'D', 'C']
        self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

    def test_shift_reduce_hard_023(self):
        entry = ('C C A A C D E B E D E B C A C C A C A C E C A C B').split()
        exepted_output = ['C', 'C', 'A', 'C', 'C', 'A', 'C', 'D', 'A', 'C',
                          'A', 'C', 'C', 'A', 'C', 'A', 'C', 'D', 'C', 'A',
                          'C', 'A']
        self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)
