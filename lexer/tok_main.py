#!/usr/bin/env python3

import sys
from utils.commands import ListCommands


from pprint import pprint

def main():
	if len(sys.argv) > 1:
		command = " ".join(sys.argv[1:])
		tokens = []
		command = ListCommands(command)
		print(command.tokens)
	else:
		print("missing command.")




if __name__ == '__main__':
	main()
