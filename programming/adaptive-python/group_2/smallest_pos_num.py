#!/usr/bin/env python3
# coding=utf-8

import sys


def find_smallest_end(num1, num2, n1_i, n2_i):
    while n1_i < len(num1) and n2_i < len(num2):
        if num1[n1_i] < num2[n2_i]:
            return True
        elif num1[n1_i] > num2[n2_i]:
            return False

        n1_i += 1
        n2_i += 1

    return True


def create_smallest_num(num1, num2):
    i, j = 0, 0
    smallest_num = ""

    while i < len(num1) and j < len(num2):
        if num1[i] == num2[j]:
            if find_smallest_end(num1, num2, i, j):
                smallest_num += num1[i]
                i += 1
            else:
                smallest_num += num2[j]
                j += 1
        elif num1[i] < num2[j]:
            smallest_num += num1[i]
            i += 1
        else:
            smallest_num += num2[j]
            j += 1

    smallest_num += num1[i:]
    smallest_num += num2[j:]

    return smallest_num


def main():
    [num1, num2] = sys.stdin.readline().split()
    print(create_smallest_num(num1, num2))


if __name__ == "__main__":
    main()