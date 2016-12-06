#!/usr/bin/env python3
# coding=utf-8


def phi(n):
    res = n
    i = 2

    while i ** 2 <= n:
        if n % i == 0:
            while n % i == 0:
                n //= i
            res -= res // i

        i += 1

    if n > 1:
        res -= res // n

    return res


def main():
    n = int(input())
    print(phi(n))


if __name__ == "__main__":
    main()
