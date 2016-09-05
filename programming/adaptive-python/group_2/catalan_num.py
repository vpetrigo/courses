#!/usr/bin/env python3
# coding=utf-8


TASK_MODULO = 1000000007


def modular_binom(n, k, mod):
    if n > k:
        num = 1
        den = 1
        if k > n - k:
            k = n - k
        for i in range(k):
            num = (num * (n - i)) % mod

        for i in range(1, k + 1):
            den = (den * i) % mod

        return num * modular_pow(den, mod - 2, mod) % mod

    return 0


def modular_pow(num, exp, mod):
    result = 1

    while exp > 0:
        if exp % 2 != 0:
            result = (result * num) % mod

        num = (num * num) % mod
        exp //= 2

    return result % mod


def catalan_num(n):
    return (modular_binom(2 * n, n, TASK_MODULO)
            * modular_pow(n + 1, TASK_MODULO - 2, TASK_MODULO) % TASK_MODULO)


def catalan_num_2(n):
    catalan_n = 1

    for i in range(n):
        catalan_n = (((4 * i + 2) * modular_pow(i + 2, TASK_MODULO - 2, TASK_MODULO)) % TASK_MODULO
                     * catalan_n % TASK_MODULO)
    return catalan_n


def main():
    n = int(input())
    ans = catalan_num_2(n)
    print(ans)


if __name__ == "__main__":
    main()
