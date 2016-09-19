#!/usr/bin/env python3
# coding=utf-8


import sys
import numpy


def main():
    N, M = tuple(map(int, sys.stdin.readline().split()))
    arr = (tuple(map(int, line.split())) for line in sys.stdin)
    A, b = numpy.hsplit(numpy.array(tuple(arr)).reshape((N, M + 1)), (M,))
    solutions = numpy.linalg.lstsq(A, b)[0]
    print(" ".join(str(x) for [x] in solutions))


if __name__ == "__main__":
    main()
