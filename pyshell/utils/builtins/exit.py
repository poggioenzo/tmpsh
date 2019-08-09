import sys

def exit(argv, environ):
    if len(argv) >= 2:
        print("exit: too many arguments.", file=sys.stderr)
        return 1
    status = int(argv[0]) if len(argv) == 1 else 0
    sys.exit(status)
