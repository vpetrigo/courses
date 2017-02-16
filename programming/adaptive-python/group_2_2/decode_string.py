#!/usr/bin/env python3
# coding=utf-8


import re


def main():
    enc_string = input()
    pattern = re.compile("\d*[a-zA-Z]")

    for code in pattern.finditer(enc_string):
        num = ''
        for ch in code[0]:
            if ch.isdigit():
                num += ch

        if not num:
            num = '1'

        print(code[0][-1] * int(num), end='')


if __name__ == "__main__":
    main()
