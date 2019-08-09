#!/usr/bin/env python3

import sys
import os

if __name__ == "__main__":
    print("start of reader")
    content = sys.stdin.read()
    print(sys.argv[0] + " : " + content)
    print("ALSO : |{}|".format(open(sys.argv[1]).read()))
    import time
    time.sleep(2)
    print("end of reader")
    pass
