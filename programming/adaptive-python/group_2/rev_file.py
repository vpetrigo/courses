#!/usr/bin/env python3
# coding=utf-8


import sys


def main():
    reader = (line for line in open("dataset_28255_1.txt"))

    with open("output_28255_1.txt", "w") as f:
        for line in reversed(list(reader)):
            print(line, file=f, end="")


if __name__ == "__main__":
    main()
