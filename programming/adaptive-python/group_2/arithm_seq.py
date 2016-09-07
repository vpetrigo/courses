#!/usr/bin/env python3
# coding=utf-8


import sys


def is_arithm_seq(seq):
    if len(seq) >= 2:
        d = seq[1] - seq[0]
        a_1 = seq[0]

        for i in range(1, len(seq)):
            if seq[i] != a_1 + i * d:
                return False
        else:
            return True

    return True


def main():
    sequence = list(map(int, sys.stdin.readline().split()))
    sequence = sorted(sequence)

    if is_arithm_seq(sequence):
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
