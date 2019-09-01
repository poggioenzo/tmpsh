#!/usr/bin/env python3

FILES = [
        "test.sh",
        ]

def get_outputs(filename):
    tmpsh_output =


def run_test():
    for filename in FILES:
        print("Test for {}\n".format(filename))
        status = os.system("diff ")


if __name__ == "__main__":
    pass
