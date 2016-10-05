#!/usr/bin/env python3
# coding=utf-8


def filter_positive(seq):
    return list(filter(lambda x: x > 0, seq))


def main():
    seq = tuple(map(int, input().split()))
    print(*filter_positive(seq))


if __name__ == "__main__":
    main()
