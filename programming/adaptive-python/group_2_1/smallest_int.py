#!/usr/bin/env python3
# coding=utf-8


def gcd(a, b):
    while b > 0:
        a, b = b, a % b

    return a


def main():
    a, b = map(int, input().split())
    d = gcd(a, b)

    print((a * b) // d)


if __name__ == "__main__":
    main()
