#!/usr/bin/env python3

import time


def sleeper(value):
    print("constructor")

    def mon_decorator(my_func):
        print("wrapper")

        def my_new_func(self, i):
            time.sleep(value)
            print("start")
            res = my_func(self, i)
            print("end")
            return res

        return my_new_func
    return mon_decorator


@sleeper(2)
def mon_test(*args):
    print("in test")
    pass


mon_test(1, 2)
