#!/usr/bin/env python3
# coding=utf-8


import itertools


def main():
    seq_data_n, var_callers_n = map(int, input().split())
    print(2 + seq_data_n + seq_data_n * var_callers_n +
            seq_data_n * var_callers_n * (var_callers_n - 1) // 2)


if __name__ == "__main__":
    main()
