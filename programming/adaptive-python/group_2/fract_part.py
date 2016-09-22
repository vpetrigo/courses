#!/usr/bin/env python3
# coding=utf-8


def main():
    n = input().split(".")
    n = 0 if len(n) == 1 else n[-1]
    print("0.{}".format(n))


if __name__ == "__main__":
    main()
