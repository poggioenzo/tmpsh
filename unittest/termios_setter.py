#!/usr/bin/env python3

import unittest
from unittest import TestCase, TextTestRunner
from ProjectFuncCffi import ffi, lib

class Test_termios_setter(TestCase):

	def test_termios_setter(self):
		self.assertEqual(lib.DEFAULT_UNIT_TEST, 0)

if __name__ == '__main__':
	print("\n\n{:*^70}".format("#:~- TERMIOS_SETTER -~:#"))
	unittest.main()
