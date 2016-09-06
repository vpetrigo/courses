#!/usr/bin/env python3
# coding=utf-8


def main():
    n = int(input())
    assert n >= 0
    START_SYMBOL = "\\"

    print(chr(ord(START_SYMBOL) + n))

if __name__ == "__main__":
    main()
