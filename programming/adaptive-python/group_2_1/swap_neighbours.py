#!/usr/bin/env python3
# coding=utf-8


def main():
    n = input()
    array = input().split()

    for i in range(0, len(array) - 1, 2):
        array[i], array[i + 1] = array[i + 1], array[i]

    print(*array)


if __name__ == "__main__":
    main()
