#!/usr/bin/env python3
# coding=utf-8

"""
Given a sequence of lines.
Output all the lines, which contain "cat" as a word.

Note:
Use the groups of symbols \b и \B to work with words.
"""


import re
import sys


def main():
    pattern = re.compile(r"\bcat\b")
    reader = (line.strip() for line in sys.stdin)

    for line in reader:
        if pattern.search(line):
            print(line)


if __name__ == "__main__":
    main()
