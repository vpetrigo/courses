#!/usr/bin/env python3
# coding=utf-8


import sys


def is_breakable(n, m, segment_size):
    """
    Function determines whether it is possible to break off chocolate bar
    (n * m size) to exactly of given @segment_size in one cut
    example:
    n=2 m=4 segment_size=6 -> YES
    n=2 m=10 segment_size=7 -> NO
    """
    choc_size = n * m
    rest_bar = choc_size - segment_size

    if (choc_size >= segment_size and
            (rest_bar % n == 0 or rest_bar % m == 0)):
            return True
    return False


def main():
    reader = (int(line) for line in sys.stdin)
    n, m, segment_size = reader

    if is_breakable(n, m, segment_size):
        print("YES")
    else:
        print("NO")


if __name__ == "__main__":
    main()
