#!/usr/bin/env python3
# coding=utf-8


import sys


def read_data():
    for line in sys.stdin:
        yield tuple(tuple(map(int, cycle.split()))
                    for cycle in line.split(";"))


def find_phi(sigma, alpha):
    def find_map(v):
        for m in alpha:
            if v in m:
                return m[(m.index(v) + 1) % len(m)]

    phi = []

    for s in sigma:
        cycle = [s[0]]
        v = find_map(cycle[-1])

        while v != cycle[0]:
            cycle.append(v)
            v = find_map(cycle[-1])

        phi.append(cycle)

    return phi


def main():
    reader = read_data()
    sigma = next(reader)
    alpha = next(reader)
    phi = find_phi(sigma, alpha)
    print("PHI:", phi)
    print((2 - len(sigma) + len(alpha) - len(phi) // 2) // 2)


if __name__ == "__main__":
    main()
