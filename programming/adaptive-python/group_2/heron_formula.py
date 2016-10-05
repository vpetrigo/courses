#!/usr/bin/env python3
# coding=utf-8

import math
import sys


def main():
    reader = (int(line) for line in sys.stdin)
    [a, b, c] = [next(reader) for _ in range(3)]
    p = (a + b + c) / 2
    triangle_area = math.sqrt(p * (p - a) * (p - b) * (p - c))
    print(triangle_area)


if __name__ == "__main__":
    main()
