#!/usr/bin/env python3

import os


def write_file(filename, text):
    with open(filename, 'w') as fd:
        fd.write(text)
        fd.close()


def get_text(filename):
    text = ""
    with open(filename, 'r') as fd:
        text = fd.read()
        fd.close()
    return text
