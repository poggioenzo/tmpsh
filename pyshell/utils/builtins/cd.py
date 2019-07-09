import os

def cd(argv, environ):
    try:
        os.chdir(argv[0])
        return 0
    except:
        return 1
