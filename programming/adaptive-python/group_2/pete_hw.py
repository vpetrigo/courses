#!/usr/bin/env python3
# coding=utf-8

import sys
import collections
import string


def main():
    dict_size = int(input())
    teacher_dict = collections.defaultdict(list)

    for _ in range(dict_size):
        word = sys.stdin.readline().strip()
        key, val = "".join(list(map(str.lower, word))), word
        teacher_dict[key].append(val)

    writing = sys.stdin.readline().split()
    mistakes = 0

    for word in writing:
        if word.lower() not in teacher_dict:
            emph_letters = sum(1 for ch in word if ch in string.ascii_uppercase)

            if emph_letters > 1 or emph_letters == 0:
                mistakes += 1
        else:
            if word not in teacher_dict[word.lower()]:
                mistakes += 1

    print(mistakes)

if __name__ == "__main__":
    main()