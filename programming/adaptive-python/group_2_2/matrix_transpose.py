#!/usr/bin/env python3
# coding=utf-8


def main():
    n, m, *matrix = tuple(map(int, input().split()))
    print(' '.join([' '.join(map(str, matrix[i::m])) for i in range(m)]))

if __name__ == "__main__":
    main()
