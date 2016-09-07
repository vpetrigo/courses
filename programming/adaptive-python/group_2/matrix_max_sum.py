#!/usr/bin/env python3
# coding=utf-8

import math
import sys


def test_matrix(matrix, row_len):
    for row in matrix:
        assert len(row) == row_len


def row_max_sum(row):
    cur_sum = max_sum = -math.inf

    for element in row:
        cur_sum = max(element, cur_sum + element)
        max_sum = max(max_sum, cur_sum)

    return max_sum


def get_max_sum(matrix):
    row_length = len(matrix[0])
    matrix_length = len(matrix)
    row_index = 0
    max_sum = -math.inf

    for i in range(matrix_length):
        # reset submatrix summation list at the each step
        cur_row = [0 for i in range(row_length)]
        for j in range(i, matrix_length):
            # get sum over the all rows that are higher
            cur_row = [x + y for x, y in zip(cur_row, matrix[j])]
            cur_sum = row_max_sum(cur_row)

            if cur_sum > max_sum:
                max_sum = cur_sum

    return max_sum


def main():
    reader = (tuple(map(int, line.split())) for line in sys.stdin)
    M, N = next(reader)
    matrix = [next(reader) for _ in range(M)]
    test_matrix(matrix, N)
    print(get_max_sum(matrix))


if __name__ == "__main__":
    main()
