#!/usr/bin/env python3
# coding=utf-8


import sys


def is_beating(x1, y1, x2, y2):
    if x1 == x2 or y1 == y2 or abs(x1 - x2) == abs(y1 - y2):
        return True

    return False


def main():
    coords = sys.stdin.readline().split()
    x1, y1, x2, y2 = map(int, coords)

    if is_beating(x1, y1, x2, y2):
        print("YES")
    else:
        print("NO")


if __name__ == "__main__":
    main()
