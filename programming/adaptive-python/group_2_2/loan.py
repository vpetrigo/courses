#!/usr/bin/env python3
# coding=utf-8


import sys


def main():
    reader = (line for line in sys.stdin)
    [p_amount, a_nominal, n_of_times, t_years] = [float(next(reader)) for _ in range(4)]
    print(p_amount * (1 + a_nominal / n_of_times) ** (n_of_times * t_years))


if __name__ == "__main__":
    main()
