#!/usr/bin/env python3
# coding=utf-8


def main():
    n = int(input())

    if n > 1 or n == 0:
        print("{} programmers".format(n))
    else:
        print("{} programmer".format(n))


if __name__ == "__main__":
    main()
