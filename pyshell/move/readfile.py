#!/usr/bin/env python3

import os

def read_file(fd):
    file_content = ""
    while 1:
        buffer = os.read(fd, 1024).decode()
        if len(buffer) == 0:
            break
        print(buffer, end="")
        file_content += buffer
    return file_content

print("start read")
read_file(0)


