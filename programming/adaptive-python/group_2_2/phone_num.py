#!/usr/bin/env python3
# coding=utf-8


import re


def main():
    pnum = re.fullmatch("^19\d{9}$", input())
    print("Yes" if pnum else "No")


if __name__ == "__main__":
    main()
