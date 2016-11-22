#!/usr/bin/env python3
# coding=utf-8

"""
Вашей программе на вход поступает пара строк: описания перестановок σ и α.
Формат записи: для каждой перестановки записываются ее циклы, разделенные
точкой с запятой. Внутри цикла элементы разделяются пробелами.
Например, "1 5 3 2;4 6" отвечает перестановке 1→5;5→3;3→2;2→1;4→6;6→4.
Гарантируется, что перестановки имеют четную длину от 2 до 100 и корректно
определяют некоторую карту. Вывести единственное число — род поверхности, на
которую уложена эта карта.
"""


import sys


def read_data(stream):
    for line in stream:
        yield tuple(tuple(map(int, cycle.split()))
                    for cycle in line.split(";"))


def find_phi(sigma, alpha):
    def find_map(v, perm):
        for c in perm:
            if v in c:
                return c[(c.index(v) + 1) % len(c)]

    def get_cycle(v):
        if not processed[v - 1]:
            cycle = []
            cycle.append(v)

            while True:
                processed[v - 1] = True
                mv = find_map(v, alpha)
                n = find_map(mv, sigma)

                if n == cycle[0]:
                    break

                cycle.append(n)
                v = n

            return cycle

    phi = []
    processed = [False for _ in range(2 * len(alpha))]

    for s in alpha:
        a, b = s
        c1 = get_cycle(a)
        c2 = get_cycle(b)

        if c1:
            phi.append(c1)
        if c2:
            phi.append(c2)

    return phi


def count_holes(sigma, alpha, phi):
    return (2 - len(sigma) + len(alpha) - len(phi)) // 2


def main():
    reader = read_data(sys.stdin)
    sigma = next(reader)
    alpha = next(reader)
    phi = find_phi(sigma, alpha)

    print(count_holes(sigma, alpha, phi))


if __name__ == "__main__":
    main()
