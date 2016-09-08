#!/usr/bin/env python3
# coding=utf-8


import numpy as np
import urllib.request as urlreq


def main():
    f_input = input()
    # https://stepic.org/media/attachments/lesson/16462/boston_houses.csv
    file = urlreq.urlopen(f_input)
    data = np.loadtxt(file, delimiter=",", skiprows=1)
    y, *factors = np.hsplit(data, len(data[0]))
    y_1 = np.hstack(y)
    A = np.array([np.ones_like(y_1)])
    A = np.append(A, tuple(np.hstack(factor) for factor in factors), axis=0)
    b = np.linalg.lstsq(A.T, y_1)[0]
    print(" ".join(map(str, b)))


if __name__ == "__main__":
    main()
