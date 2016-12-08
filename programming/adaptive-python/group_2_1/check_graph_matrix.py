#!/usr/bin/env python3
# coding=utf-8


import sys


def naive_adj_matrix_check(matrix):
    n = len(matrix)

    for i in range(n):
        for j in range(n):
            if matrix[i][j] != matrix[j][i]:
                return False
    else:
        return True


def main():
    reader = (tuple(map(int, line.split())) for line in sys.stdin)
    n, *e = next(reader)
    matrix = tuple(next(reader) for _ in range(n))

    print("YES" if naive_adj_matrix_check(matrix) else "NO")


if __name__ == "__main__":
    main()
