import os
import utils.execution.variables as variables
import sys

def cd(argv, environ):
    if len(argv) >= 2:
        print("cd: too many arguments.", file=sys.stderr)
        return 1
    if len(argv) == 0:
        new_dir = variables.getenv("HOME")
    else:
        new_dir = argv[0]
    try:
        os.chdir(new_dir)
        return 0
    except:
        err_msg = f"cd: No such file or directory: {new_dir}"
        print(err_msg, file=sys.stderr)
        return 1
