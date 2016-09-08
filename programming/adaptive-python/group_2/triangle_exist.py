#!/usr/bin/env python3
# coding=utf-8


import sys


def main():
    reader = (int(line) for line in sys.stdin)
    a, b, c = reader

    if a < b + c and b < a + c and c < a + b:
        print("YES")
    else:
        print("NO")


if __name__ == "__main__":
    main()
