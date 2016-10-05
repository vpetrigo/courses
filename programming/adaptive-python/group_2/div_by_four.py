#!/usr/bin/env python3
# coding=utf-8

import sys


def main():
    reader = (int(line) for line in sys.stdin)
    n = next(reader)
    seq = tuple(next(reader) for _ in range(n))
    print(max(filter(lambda e: e % 4 == 0, seq)))


if __name__ == "__main__":
    main()
