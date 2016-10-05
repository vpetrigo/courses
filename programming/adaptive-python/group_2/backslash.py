#!/usr/bin/env python3
# coding=utf-8


import sys


def main():
    reader = (line for line in sys.stdin if line.find("\\") != -1)
    print(*reader, sep="")


if __name__ == "__main__":
    main()
