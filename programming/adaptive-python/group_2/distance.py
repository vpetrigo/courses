#!/usr/bin/env python3
# coding=utf-8


import sys
import math


def distance(x1, y1, x2, y2):
    return math.sqrt((x1 - x2) ** 2 + (y1 - y2) ** 2)


def main():
    x1, y1, x2, y2 = [float(x) for x in sys.stdin]
    print(distance(x1, y1, x2, y2))


if __name__ == "__main__":
    main()
