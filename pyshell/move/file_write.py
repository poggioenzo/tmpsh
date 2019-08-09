#!/usr/bin/env python3

import sys
import time

if __name__ == "__main__":
    print("start of writer on : {}".format(sys.argv[1]))
    to_fill = open(sys.argv[1], "w")
    print(to_fill.write("My huge str\n"))
    time.sleep(2)
    print(to_fill.write("My huge strbis"))
    print("end of writer")
    pass
