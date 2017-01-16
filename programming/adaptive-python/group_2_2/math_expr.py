#!/usr/bin/env python3
# coding=utf-8


import operator


OP_DICT = {
    "plus": operator.add,
    "minus": operator.sub,
    "divide": operator.floordiv,
    "multiply": operator.mul
}


def main():
    a, op, b = input().split()
    print(OP_DICT[op](int(a), int(b)))


if __name__ == "__main__":
    main()