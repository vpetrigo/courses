#!/usr/bin/env python3
# coding=utf-8

import re


def main():
    reg_num = re.compile(r"^[ABEKMHOPCTYX]\d{3}[ABEKMHOPCTYX]{2}$")

    if reg_num.match(input()):
        print("Yes")
    else:
        print("No")


if __name__ == "__main__":
    main()
