#!/usr/bin/env python3
# coding=utf-8


import sys
import math


def karatsuba(a, b):
    if a < 10 or b < 10:
        return a * b

    square_2 = int(math.floor(max(math.log2(a), math.log2(b)))) + 1
    if square_2 % 2 != 0:
        square_2 += 1
    half_square_2 = math.ceil(square_2 / 2)

    a_l = a >> half_square_2
    a_r = a & ((1 << half_square_2) - 1)
    b_l = b >> half_square_2
    b_r = b & ((1 << half_square_2) - 1)

    P1 = karatsuba(a_l, b_l)
    P2 = karatsuba(a_r, b_r)
    P3 = karatsuba(a_r + a_l, b_r + b_l)

    return P1 * 2 ** square_2 + (P3 - P1 - P2) * 2 ** half_square_2 + P2


def main():
    reader = (int(line) for line in sys.stdin)
    a = next(reader)
    b = next(reader)

    print(karatsuba(a, b))


if __name__ == "__main__":
    main()
