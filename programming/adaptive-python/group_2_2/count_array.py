#!/usr/bin/env python3
# coding=utf-8


def main():
    n, m = map(int, input().split())
    counter = [0] * m
    vals = tuple(map(int, input().split()))

    for v in vals:
        counter[v - 1] += 1

    print(*counter)


if __name__ == "__main__":
    main()
