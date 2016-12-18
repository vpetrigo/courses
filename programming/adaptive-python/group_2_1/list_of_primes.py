#!/usr/bin/env python3
# coding=utf-8


import sys


def gen_primes():
    i = 2
    marked = {}

    while True:
        if i not in marked:
            yield i

            marked[i * i] = [i]
        else:
            for p in marked[i]:
                marked.setdefault(p + i, []).append(p)

            del marked[i]

        i += 1


def main():
    primes_border = 20000
    reader = (tuple(map(int, line.split())) for line in sys.stdin)
    n, *e = next(reader)
    prime_indexes = next(reader)
    pr_gen = gen_primes()
    pr_list = [next(pr_gen) for _ in range(primes_border)]

    print(*[pr_list[i - 1] for i in prime_indexes])


if __name__ == "__main__":
    main()
