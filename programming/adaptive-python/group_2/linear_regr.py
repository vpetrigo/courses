#!/usr/bin/env python3
# coding=utf-8


import numpy as np
import urllib.request as urlreq


def main():
    f_input = input()
    file = urlreq.urlopen(f_input)
    data = np.loadtxt(file, delimiter=",", skiprows=1)
    y, *factors = np.hsplit(data, len(data[0]))
    y_1 = np.hstack(y)
    A = np.stack((np.hstack(fact) for fact in factors))
    A = np.concatenate((A, [np.ones_like(y_1)]))
    b = np.linalg.lstsq(A.T, y_1)[0]
    b = np.concatenate(([b[-1]], b[:-1]))
    print(" ".join(map(str, b)))


if __name__ == "__main__":
    main()
