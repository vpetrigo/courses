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
    A = np.concatenate(tuple(np.hstack(fact) for fact in factors))
    print(A)
    A = np.concatenate((A, [np.ones_like(y_1)]))
    print(" ".join(map(str, np.linalg.lstsq(A.T, y_1)[0])))


if __name__ == "__main__":
    main()
