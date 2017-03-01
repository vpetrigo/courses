#!/usr/bin/env python3
# coding=utf-8


import itertools


def main():
    seq = input()
    groups = [(k, len(tuple(g))) for k, g in itertools.groupby(seq)]

    print("".join(str(a) + str(b) for (a, b) in groups))


if __name__ == "__main__":
    main()
