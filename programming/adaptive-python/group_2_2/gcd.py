#!/usr/bin/env python3
# coding=utf-8


import sys


def gcd(a, b):
    while b > 0:
        a, b = b, a % b

    return a


def main():
    reader = (tuple(map(int, line.split())) for line in sys.stdin)
    a, b = next(reader)
    print(gcd(a, b))


if __name__ == "__main__":
    main()