import utils.global_var as gv
import sys

class HashExec:
    def __init__(self, exec_file):
        self.exec_file = exec_file
        self.count = 0

def display_hash(argv):
    if len(gv.HASH) == 0:
        print("hash: hash table empty", file=sys.stderr)
        return 1
    print("hits    command")
    for cmd in gv.HASH:
        hash_cmd = gv.HASH[cmd]
        print("%4.4d    %s" % (hash_cmd.count, hash_cmd.exec_file))
    return 0


def hash(argv, environ):
    if len(argv) == 0:
        return display_hash(argv)
    elif argv[0] == "-r":
        gv.HASH.clear()
    elif argv[0] == "-p":
        new_path = argv[1]
        command = argv[2]
        gv.HASH[command] = HashExec(new_path)
    else:
        for argument in argv:
            hash_cmd = gv.HASH.get(argument, None)
            if hash_cmd is None:
                print("hash: {} not found".format(argument))
                return 1
            hash_cmd.count = 0
    return 0

