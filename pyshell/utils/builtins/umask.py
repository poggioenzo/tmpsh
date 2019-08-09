import os
import sys

def umask(argv, environ):
    """
    Display or change the current umask.
    """
    if len(argv) == 0:
        curr_umask = os.umask(0o22)
        os.umask(curr_umask)
        print("%#3o" % curr_umask)
        return 0
    elif len(sys.argv) >= 2:
        print("umask: too many arguments", file=sys.stderr)
        return 1
    new_mask = int(argv[0], base=8)
    if 0 <= new_mask <= 0o777:
        os.umask(new_mask)
        return 0
    else:
        print("umask: bas umask", file=sys.stderr)
        return 1


