#!/usr/bin/env python3
# coding=utf-8


def modify_list(l: list):
    l[:] = [elem // 2 for elem in l if elem % 2 == 0]


def main():
    l = [1, 2, 3, 4, 5, 6]
    modify_list(l)
    print(l)
    modify_list(l)
    print(l)


if __name__ == "__main__":
    main()
