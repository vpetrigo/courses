#!/usr/bin/env python3
# coding=utf-8


def main():
    string = input()
    splits = tuple(map(int, input().split()))

    print(" ".join((string[splits[0]:splits[1] + 1], string[splits[-2]:splits[-1] + 1])))


if __name__ == "__main__":
    main()
