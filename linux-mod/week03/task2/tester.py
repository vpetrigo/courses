#!/usr/bin/env python3
# coding=utf-8


import os


fd = os.open("/dev/solution", os.O_RDWR | os.O_NOCTTY)
test = open(fd, "wb+", buffering=0)
test.write(b"Hello")
data = test.read()
print(data)
data = test.read()
print(data)
