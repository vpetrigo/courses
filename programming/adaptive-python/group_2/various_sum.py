#!/usr/bin/env python3
# coding=utf-8
"""
Given N integers A_1, A_2, ..., A_N. You should find the number of various
sum values of k_1 * A_1 + k_2 * A_2 + ... + k_N * A_N.

Input data

The first line contains number N, the second – A_1, A_2, ..., A_N separated
by a space. All numbers are integers:

1 ≤ N ≤ 500,

0 ≤ A_i ≤100,

k_i = 0 | 1

Output data

Output the number of the various sum values.

Sample Input:
3
1 2 3
Sample Output:
7
"""


def various_sum(seq):
    ds = set([0])
    cur_sums = set()

    for elem in seq:
        for s in ds:
            cur_sums.add(elem + s)
        ds.update(cur_sums)

    return len(ds)


def main():
    N = int(input())
    seq = tuple(map(int, input().split()))

    print(various_sum(seq))


if __name__ == "__main__":
    main()
