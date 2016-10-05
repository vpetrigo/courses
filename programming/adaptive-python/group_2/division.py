#!/usr/bin/env python3
# coding=utf-8


def is_divisable(a, b=3):
    return a == a // b * b


def main():
    number = int(input())
    print("YES" if is_divisable(number) else "NO")


if __name__ == "__main__":
    main()
