#!/usr/bin/env python3
import time

if __name__ == "__main__":
    tty = open("/dev/tty", "w")
    print("start sleeper", file=tty)
    for i in range(2):
        print("content {}".format(i))
        time.sleep(1)
    print("end sleeper", file=tty)
