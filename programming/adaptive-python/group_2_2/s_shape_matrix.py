#!/usr/bin/env python3
# coding=utf-8


import sys


def main():
    n, m = map(int, input().split())

    for i in range(n):
        counter = (i + 1) * m
        for j in range(m):
            if i % 2 == 0:
                out = counter - m + j + 1
            else:
                out = counter - j

            sys.stdout.write("{:>4d}".format(out))

        sys.stdout.write("\n")


if __name__ == "__main__":
    main()
