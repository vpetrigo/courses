#!/usr/bin/env python3
# coding=utf-8


import sys
import re


def is_assignment(line):
    pattern = (r"^\s*\b[^#]?\b([a-zA-Z_]+[0-9\.\w]*)(,\s*"
               r"[a-zA-Z_]+[0-9\.\w]*)* = .+$")

    return re.match(pattern, line)


def main():
    line_num = 1

    for line in sys.stdin:
        if is_assignment(line):
            vars_part = line.split("=")[0]

            if vars_part.find("..") == -1:
                vars_part = tuple(map(str.strip, vars_part.split(", ")))
                print(line_num, " ".join(vars_part))

        line_num += 1


if __name__ == "__main__":
    main()
