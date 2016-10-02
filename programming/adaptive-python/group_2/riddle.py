#!/usr/bin/env python3
# coding=utf-8


PATTERN = ("{0} and {1} sat in the tree.\n"
           "{0} had fallen, {1} was stolen.\n"
           "What's remaining in the tree?")


def main():
    a1, a2 = input(), input()
    print(PATTERN.format(a1, a2))


if __name__ == "__main__":
    main()
