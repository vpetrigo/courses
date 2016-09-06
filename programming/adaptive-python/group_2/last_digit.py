#!/usr/bin/env python3
# coding=utf-8


def get_digit(num, digit):
    digit_num = 0

    while num > 0 and digit > 0:
        digit_num = num % 10
        num //= 10
        digit -= 1

    return digit_num


def main():
    n = int(input())
    print(get_digit(n, 1))


if __name__ == "__main__":
    main()
