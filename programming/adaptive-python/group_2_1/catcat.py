#!/usr/bin/env python3
# coding=utf-8

import re
import sys


def main():
    checker = re.compile(r"(cat).*\1")

    for line in sys.stdin:
        if checker.search(line):
            print(line.rstrip())


if __name__ == "__main__":
    main()
