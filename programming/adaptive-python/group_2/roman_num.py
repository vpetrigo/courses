#!/usr/bin/env python3
# coding=utf-8

ROMAN_NUM = {"I": 1, "V": 5, "X": 10,
             "L": 50, "C": 100, "D": 500,
             "M": 1000}


def roman_to_dec(r_num):
    result = 0

    prev_ch = r_num[-1]
    for digit in r_num[::-1]:
        if ROMAN_NUM[prev_ch] > ROMAN_NUM[digit]:
            result -= ROMAN_NUM[digit]
        else:
            result += ROMAN_NUM[digit]
        prev_ch = digit

    return result


def main():
    num = input().strip()
    print(roman_to_dec(num))


if __name__ == "__main__":
    main()
