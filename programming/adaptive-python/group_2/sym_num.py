#!/usr/bin/env python3
# coding=utf-8


def main():
    num = input().zfill(4)
    print(1 if num == num[::-1] else 0)


if __name__ == "__main__":
    main()
