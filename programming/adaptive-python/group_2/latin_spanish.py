#!/usr/bin/env python3
# coding=utf-8


import sys
import collections


def latin_spanish_dict(n_words, reader):
    for _ in range(n_words):
        term, descript = next(reader).split(" - ")
        # tuple of "latin keyword", "description"
        yield term, map(str.strip, descript.split(", "))


def spanish_latin_dict(latin_dict):
    sl_dict = collections.defaultdict(list)

    for k, v in latin_dict:
        for descr in v:
            sl_dict[descr].append(k)

    return sl_dict


def print_dict(dictionary):
    for k in sorted(dictionary.keys()):
        print("{} - {}".format(k, ", ".join(sorted(dictionary[k]))))


def main():
    reader = (line for line in sys.stdin)
    n = int(next(reader))
    ls_dict = latin_spanish_dict(n, reader)
    sl_dict = spanish_latin_dict(ls_dict)

    print(len(sl_dict))
    print_dict(sl_dict)


if __name__ == "__main__":
    main()
