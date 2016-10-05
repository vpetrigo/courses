#!/usr/bin/env python3
# coding=utf-8


def main():
    n = int(input())
    assert n > 0

    if n % 2 != 0:
        n = n + 1
    else:
        n = n + 2

    print(n)


if __name__ == "__main__":
    main()
