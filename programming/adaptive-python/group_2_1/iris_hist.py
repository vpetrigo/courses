#!/usr/bin/env python3
# coding=utf-8

"""
At your individual Iris dataset take “Sepal length” (the first column)
feature and find the histogram with 10 bins (left-open intervals).
Put the array of frequencies at the bins in the order of bins as your output.

Sample Input:
4.3	3.0	1.1	0.1	I.setosa
7.7	3.0	6.1	2.3	I.virginica
Sample Output:
1 0 0 0 0 0 0 0 0 1
"""

import numpy
import math


def build_hist(data):
    l = min(data)
    r = max(data)
    epsilon = 0.001
    bins = 10
    step = (r - l) / 10
    seq = [l + i * step for i in range(bins + 1)]
    for i in range(1, bins + 1):
        seq[i] += epsilon

    return numpy.histogram(data, bins=seq)


def main():
    with open("dataset_30642_1.txt") as tfile:
        n = [float(line.split()[0]) for line in tfile]
        print(*build_hist(n)[0])


if __name__ == "__main__":
    main()
