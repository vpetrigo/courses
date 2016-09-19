#!/usr/bin/env python3
# coding=utf-8

import sys


def largest_cons_div_seq(seq):
    seq_len = len(seq)
    count_arr = [1 for _ in range(seq_len)]

    for i in range(seq_len):
        for j in range(i):
            if seq[i] >= seq[j] and seq[i] % seq[j] == 0:
                count_arr[i] = max(count_arr[i], count_arr[j] + 1)

    return max(count_arr)


def main():
    N = int(input())
    input_seq = tuple(map(int, sys.stdin.readline().split()))
    print(largest_cons_div_seq(input_seq))


if __name__ == "__main__":
    main()
