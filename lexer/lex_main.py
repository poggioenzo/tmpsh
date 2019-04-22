#!/usr/bin/env python3

import sys
from utils.commands import ListCommands
import code

def main():
	if len(sys.argv) == 1:
		lc = ListCommands("ls -l; echo 'lol' 1;$(echo ls)\\\ncat ../*")
	else :
		print(" ".join(sys.argv[1:]))
		lc = ListCommands(" ".join(sys.argv[1:]))
	#code.interact(local = locals())
	print([ lc.tokens[x.start:x.end] for x in lc.tree_commands])


if __name__ == '__main__':
	main()
