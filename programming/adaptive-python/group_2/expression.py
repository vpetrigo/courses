#!/usr/bin/env python3
# coding=utf-8


def calc_expr(a, b, c):
    return (a + b * c) / 5 - a ** 3 + (a + c / 3) / 4


def main():
    a, b, c = map(int, input().split())
    print(calc_expr(a, b, c))


if __name__ == "__main__":
    main()
