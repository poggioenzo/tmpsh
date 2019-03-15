#!/usr/bin/env python3

import unittest
from unittest import TestCase, TextTestRunner
from ProjectFuncCffi import ffi, lib

class Test_debug(TestCase):

	def test_debug(self):
		self.assertEqual(lib.DEFAULT_UNIT_TEST, 0)

if __name__ == '__main__':
	print("\n\n{:*^70}".format("#:~- DEBUG -~:#"))
	unittest.main()
