#!/usr/bin/env python3
# coding=utf-8


def main():
    alpha_cipher = [input(), input()]
    for t in alpha_cipher, alpha_cipher[::-1]:
        print(input().translate(str.maketrans(*t)))


if __name__ == "__main__":
    main()
