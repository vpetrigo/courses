#!/usr/bin/env python3
# coding=utf-8


import math
import itertools


def gcd(a, b):
    if b == 0:
        return a

    return gcd(b, a % b)


def primes():
    i = 2
    is_prime = True

    while True:
        border = math.floor(math.sqrt(i))

        for j in range(2, border + 1):
            if gcd(i, j) != 1:
                is_prime = False
                break
        else:
            yield i

        i += 1


def test():
    assert gcd(0, 0) == 0
    assert gcd(1, 0) == 1
    assert gcd(0, 1) == 1
    assert gcd(256, 43) == math.gcd(256, 43)
    gen = primes()
    assert next(gen) == 2
    assert next(gen) == 3
    assert next(gen) == 5


if __name__ == "__main__":
    test()
    print(list(itertools.takewhile(lambda x: x <= 31, primes())))
