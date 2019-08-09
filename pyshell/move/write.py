#!/usr/bin/env python3

import stat
import os
import time
import sys

if __name__ == "__main__":
    print("start write")
    print("read from {}.".format(sys.argv[1]))
    file = open(sys.argv[1])
    content = file.read()
    print("{} : {}".format(sys.argv[0], content), end="")
    print("end write")
    pass
