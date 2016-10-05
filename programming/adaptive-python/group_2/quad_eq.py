#!/usr/bin/env python3
# coding=utf-8

import sys
import math


def solve_quad_eq(a, b, c):
    d = b ** 2 - 4 * a * c

    if d >= 0:
        d_sqrt = math.sqrt(d)
        if d == 0:
            return [-b / 2 / a]

        return sorted([(-b - d_sqrt) / 2 / a, (-b + d_sqrt) / 2 / a])


def main():
    reader = (float(line) for line in sys.stdin)
    a, b, c = [next(reader) for _ in range(3)]

    sol = solve_quad_eq(a, b, c)
    if sol is not None:
        print(*sol)


if __name__ == "__main__":
    main()
