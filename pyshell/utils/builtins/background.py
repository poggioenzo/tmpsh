import utils.global_var as gv

def jobs(argv, environ):
    for task in gv.JOBS:
        pid = task[0]
        command = task[1]
        print("{} : {}".format(pid, command))
