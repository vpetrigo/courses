#!/usr/bin/env python3
# coding=utf-8


import sys


def main():
    reader = (int(line) for line in sys.stdin)
    long_side, short_side, X, Y = reader

    if short_side > long_side:
        long_side, short_side = short_side, long_side

    print(min(X, Y, abs(long_side - Y), abs(short_side - X)))


if __name__ == "__main__":
    main()
