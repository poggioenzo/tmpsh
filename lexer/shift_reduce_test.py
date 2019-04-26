#!/usr/bin/env python3

import sys
from utils.readgrammar import Grammar
import utils.shift_reduce as sr
import unittest

GRAMMAR = Grammar("grammar_test.txt")

class testShiftReduce(unittest.TestCase):

	def testShiftReduce001(self):
		entry = ''.split()
		exepted_output = []
		self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

	def testShiftReduce002(self):
		entry = 'A'.split()
		exepted_output = ['A']
		self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

	def testShiftReduce003(self):
		entry = 'A B'.split()
		exepted_output = ['A']
		self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

	def testShiftReduce004(self):
		entry = 'A C C C'.split()
		exepted_output = ['A']
		self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

	def testShiftReduce005(self):
		entry = 'A B C C C'.split()
		exepted_output = ['A']
		self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

	def testShiftReduce006(self):
		entry = 'A A'.split()
		exepted_output = ['A']
		self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

	def testShiftReduce007(self):
		entry = 'A A A'.split()
		exepted_output = ['A']
		self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

	def testShiftReduce008(self):
		entry = 'B'.split()
		exepted_output = ['A']
		self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

	def testShiftReduce009(self):
		entry = 'C C C'.split()
		exepted_output = ['A']
		self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

	def testShiftReduce010(self):
		entry = 'D D D D D D'.split()
		exepted_output = ['A']
		self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

	def testShiftReduce011(self):
		entry = 'C A'.split()
		exepted_output = ['C','A']
		self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

	def testShiftReduce012(self):
		entry = 'C B'.split()
		exepted_output = ['C','A']
		self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

	def testShiftReduce013(self):
		entry = 'E B'.split()
		exepted_output = ['D','A']
		self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

	def testShiftReduce014(self):
		entry = 'E B E'.split()
		exepted_output = ['D','A','D']
		self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

	def testShiftReduce015(self):
		entry = 'C C D D C C E E'.split()
		exepted_output = ['A']
		self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

	def testShiftReduce016(self):
		entry = 'C C D D C C E E'.split()
		exepted_output = ['A']
		self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

	def testShiftReduce017(self):
		entry = 'A B C D E'.split()
		exepted_output = ['A', 'C', 'C']
		self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

	def testShiftReduce018(self):
		entry = 'B C E C'.split()
		exepted_output = ['A', 'C','D' , 'C']
		self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

	def testShiftReduce019(self):
		entry = 'E E E D A A E E A B A A'.split()
		exepted_output = ['C', 'C', 'A', 'C', 'A']
		self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

	def testShiftReduce020(self):
		entry = '          B   D   B   E   B B C C C  E   B   D E   E   A A B A A B D E C E E B  D    C    D D  B B  E D D C'.split()
		exepted_output = ['A','D','A','D','A',       'D','A','C' , 'D'  ,'A'                    , 'D', 'C', 'C', 'A' , 'C', 'D', 'C']
		self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

	def testShiftReduce021(self):
		entry = 'SPACES D SPACES E SPACES SPACES SPACES E SPACES D SPACES A D SPACES E SPACES SPACES SPACES'.split()
		exepted_output = ['C', 'C' , 'A', 'C']
		self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

	def testShiftReduce022(self):
		entry = 'A B C E C'.split()
		exepted_output = ['A', 'C','D' , 'C']
		self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)

	def testShiftReduce023(self):
		entry = '          C    C    A A  C    D E  B    E D  E    B    C    A    C    C    A   C    A    C    E     C    A    C    B'.split()
		exepted_output = ['C', 'C', 'A', 'C', 'C', 'A', 'C', 'D', 'A', 'C', 'A', 'C', 'C', 'A','C', 'A', 'C', 'D' , 'C', 'A' ,'C', 'A' ]
		self.assertListEqual(sr.reduce_shift(entry, GRAMMAR), exepted_output)



if __name__ == '__main__':
	if len(sys.argv) == 2:
		GRAMMAR = Grammar("grammar_test.txt")
		stack = sr.reduce_shift(sys.argv[1].upper().split(), GRAMMAR)
		print(stack)
	else:
		sys.argv = [sys.argv[0]]
		unittest.main()
		#print('usage: ./shift_reduce_test.py "TAG [TAG [...]]"')
