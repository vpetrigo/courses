#!/usr/bin/env python3
# coding=utf-8


def main():
    line = input().split()
    sum = 0

    for num in line:
        try:
            sum += int(num)
        except ValueError:
            pass

    print(sum)


if __name__ == "__main__":
    main()
