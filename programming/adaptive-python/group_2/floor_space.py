#!/usr/bin/env python3
# coding=utf-8

import sys
import math


def circle():
    radius = int(input())
    pi = 3.14

    return pi * radius ** 2


def rectangle():
    length = int(input())
    width = int(input())

    return length * width


def triangle():
    reader = (int(line) for line in sys.stdin)
    a, b, c = reader
    semi_p = (a + b + c) / 2

    return math.sqrt(semi_p * (semi_p - a) * (semi_p - b) * (semi_p - c))


FLAT_TYPES = {
                "triangle": triangle,
                "circle": circle,
                "rectangle": rectangle
             }


def main():
    flat_type = input()
    print(FLAT_TYPES[flat_type]())


if __name__ == "__main__":
    main()
