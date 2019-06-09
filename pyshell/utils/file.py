#!/usr/bin/env python3


def write_file(filename, text):
    with open(filename, 'w') as file_descriptor:
        file_descriptor.write(text)
        file_descriptor.close()


def get_text(filename):
    text = ''
    with open(filename, 'r') as file_descriptor:
        text = file_descriptor.read()
        file_descriptor.close()
    return text
