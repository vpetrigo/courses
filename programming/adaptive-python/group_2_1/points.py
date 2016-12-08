#!/usr/bin/env python3
# coding=utf-8


import sys


def main():
    reader = (tuple(map(int, line.split())) for line in sys.stdin)
    n, *e = next(reader)
    points = [next(reader) for _ in range(n)]
    points = sorted(points, key=lambda x: x[0] ** 2 + x[1] ** 2)
    ans = "\n".join(" ".join(str(x) for x in y) for y in points)

    print(ans)


if __name__ == "__main__":
    main()
