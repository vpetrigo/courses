#!/usr/bin/env python3
# coding=utf-8


def get_digit(num):
    digit_num = 0

    while num > 0:
        digit_num = num % 10
        yield digit_num
        num //= 10

    return digit_num


def main():
    n = int(input())
    print(sum(get_digit(n)))


if __name__ == "__main__":
    main()
