#!/usr/bin/env python3

import sys
from utils.readgrammar import Grammar
import unittest

GRAMMAR = Grammar("grammar_test.txt")


def keyinstack(stack):
	len_stack = len(stack)
	i = 0
	while i < len_stack:
		key = ' '.join(stack[i:])
		if key in GRAMMAR.reverse:
			return True
		i += 1
	return False

def reduce(stack, goal):
	len_stack = len(stack)
	i = 0
	while i < len_stack:
		key = ' '.join(stack[i-len_stack:])
		if key != goal and key in GRAMMAR.reverse :
			stack = stack[:i - len_stack - 1 ] + [GRAMMAR.reverse[key]]
			len_stack = len(stack)
		i += 1
	return (0)

def reduce_shift(tags, goal):
	stack = []
	i = 0
	len_tags = len(tags)
	copy = tags.copy()
	while (i < len_tags):
		tag = tags[i]
		if tag == 'SPACES':
			copy.pop(0)
			i+=1
		elif keyinstack(stack):
			stack = reduce(stack, goal)
			while keyinstack(stack):
				stack = reduce(stack, goal)
		elif copy != []:
			stack.append(copy.pop(0))
			i += 1
	stack = reduce(stack, goal)
	return stack


class testShiftReduce(unittest.TestCase):

	def testShiftReduce001(self):
		entry = ''.split()
		exepted_output = []
		self.assertListEqual(reduce_shift(entry, 'A'), exepted_output)

	def testShiftReduce002(self):
		entry = 'A'.split()
		exepted_output = ['A']
		self.assertListEqual(reduce_shift(entry, 'A'), exepted_output)

	def testShiftReduce003(self):
		entry = 'A B'.split()
		exepted_output = ['A']
		self.assertListEqual(reduce_shift(entry, 'A'), exepted_output)

	def testShiftReduce004(self):
		entry = 'A C C C'.split()
		exepted_output = ['A']
		self.assertListEqual(reduce_shift(entry, 'A'), exepted_output)

	def testShiftReduce005(self):
		entry = 'A B C C C'.split()
		exepted_output = ['A']
		self.assertListEqual(reduce_shift(entry, 'A'), exepted_output)

	def testShiftReduce006(self):
		entry = 'A A'.split()
		exepted_output = ['A']
		self.assertListEqual(reduce_shift(entry, 'A'), exepted_output)

	def testShiftReduce007(self):
		entry = 'A A A'.split()
		exepted_output = ['A']
		self.assertListEqual(reduce_shift(entry, 'A'), exepted_output)

	def testShiftReduce008(self):
		entry = 'B'.split()
		exepted_output = ['A']
		self.assertListEqual(reduce_shift(entry, 'A'), exepted_output)

	def testShiftReduce009(self):
		entry = 'C C C'.split()
		exepted_output = ['A']
		self.assertListEqual(reduce_shift(entry, 'A'), exepted_output)

	def testShiftReduce010(self):
		entry = 'D D D D D D'.split()
		exepted_output = ['A']
		self.assertListEqual(reduce_shift(entry, 'A'), exepted_output)



if __name__ == '__main__':
	#print(GRAMMAR)
	if len(sys.argv) == 2:
		stack = reduce_shift(sys.argv[1].upper().split(), 'A')
		print(stack)
	else:
		sys.argv = [sys.argv[0]]
		unittest.main()
		#print('usage: ./shift_reduce_test.py "TAG [TAG [...]]"')
