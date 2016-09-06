#!/usr/bin/env python3
# coding=utf-8


def is_leap(year):
    if (year % 400 == 0 or
            (year % 4 == 0 and not year % 100 == 0)):
        return True
    return False


def main():
    year = int(input())

    if not is_leap(year):
        print("Regular")
    else:
        print("Leap")


if __name__ == "__main__":
    main()
