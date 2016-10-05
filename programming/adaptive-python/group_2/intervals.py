#!/usr/bin/env python3
# coding=utf-8


def main():
    n = int(input())

    if (-15 < n <= 12 or 14 < n < 17 or
                19 <= n):
        print(True)
    else:
        print(False)


if __name__ == "__main__":
    main()
