#!/usr/bin/env python3
# coding=utf-8


import sys


def main():
    reader = (tuple(map(int, line.split())) for line in sys.stdin)
    n, *e = next(reader)
    intervals = sorted([next(reader) for _ in range(n)], key=lambda x: x[1])
    points = []
    point = -1

    for interval in intervals:
        if point < interval[0] and point <= interval[1]:
            point = interval[1]
            points.append(point)

    print(len(points))
    print(*points)


if __name__ == "__main__":
    main()
