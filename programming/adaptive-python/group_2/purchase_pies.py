#!/usr/bin/env python3
# coding=utf-8


import sys


def main():
    reader = (int(line) for line in sys.stdin)
    a, b, n = [next(reader) for _ in range(3)]

    pies_cost = n * (a * 100 + b)
    print(pies_cost // 100, pies_cost % 100)


if __name__ == "__main__":
    main()
