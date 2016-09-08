#!/usr/bin/env python3
# coding=utf-8


def gcd(a, b):
    if a == 0 or b == 0:
        return max(a, b)
    return gcd(b % a, a)


def main():
    bio_students = int(input())
    cs_students = int(input())
    min_pie_pieces = (bio_students * cs_students //
                      gcd(bio_students, cs_students))
    print(min_pie_pieces)


if __name__ == "__main__":
    main()
