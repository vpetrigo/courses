#!/usr/bin/env python3
# coding=utf-8


import re
import sys


def main():
    pattern = re.compile(r"\byou\b")
    you_count = 0
    reader = (line for line in sys.stdin)

    for line in reader:
        you_count += len(pattern.findall(line))

    print(you_count)


if __name__ == "__main__":
    main()
