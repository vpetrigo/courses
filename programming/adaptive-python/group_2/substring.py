#!/usr/bin/env python3
# coding=utf-8

import sys


def zfunc_opt(string):
    str_len = len(string)
    z = [0 for _ in range(str_len)]
    left = 0
    right = 0

    for i in range(1, str_len):
        z[i] = max(0, min(right - i, z[i - left]))
        while (i + z[i] < str_len and
               string[z[i]] == string[i + z[i]]):
            z[i] += 1

        if i + z[i] >= right:
            left = i
            right = i + z[i]

    return z


def main():
    reader = (line.rstrip() for line in sys.stdin)
    string = next(reader)
    pattern = next(reader)
    print(zfunc_opt("$".join([pattern, string])).count(len(pattern)))


if __name__ == "__main__":
    main()
