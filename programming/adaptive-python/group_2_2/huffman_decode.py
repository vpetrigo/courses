#!/usr/bin/env python3
# coding=utf-8


def huffman_decode(code, encoded_str):
    cur_code = ""

    for ch in encoded_str:
        cur_code += ch

        if cur_code in code:
            print(code[cur_code], end="")
            cur_code = ""


def main():
    n, m = map(int, input().split())
    code = {}

    for _ in range(n):
        alpha, al_code = input().split()
        code[al_code] = alpha[:-1]

    string = input()
    huffman_decode(code, string)


if __name__ == "__main__":
    main()
