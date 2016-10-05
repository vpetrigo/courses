#!/usr/bin/env python3
# coding=utf-8


def power3(n, e):
    if n == 0 or n == 1 or e == 1:
        return n
    if e == 0:
        return 1
    if e < 0:
        return 1.0 / power3(n, -e)

    if e % 2 == 0:
        fast = power3(n, e / 2)
        return fast * fast

    return n * power3(n, e - 1)


def main():
    num = float(input())
    exp = int(input())

    print(power3(num, exp))


if __name__ == "__main__":
    main()
