#!/usr/bin/env python3

import unittest
from unittest import TestCase, TextTestRunner
from ProjectFuncCffi import ffi, lib

class Test_cursor_dependent_selection(TestCase):

	def test_cursor_dependent_selection(self):
		self.assertEqual(lib.DEFAULT_UNIT_TEST, 0)

if __name__ == '__main__':
	print("\n\n{:*^70}".format("#:~- CURSOR_DEPENDENT_SELECTION -~:#"))
	unittest.main()
