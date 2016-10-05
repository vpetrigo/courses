# /usr/bin/env python3
# coding=utf-8

import sys


def main():
    [a, b] = [float(n) for n in sys.stdin]
    print((a * b > a / b))


if __name__ == "__main__":
    main()
