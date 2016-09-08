#!/usr/bin/env python3
# coding=utf-8

import operator as op


MATH_OP = {
            "+": op.add,
            "-": op.sub,
            "/": op.truediv,
            "*": op.mul,
            "mod": op.mod,
            "div": op.floordiv,
            "pow": op.pow
          }


def main():
    a = float(input())
    b = float(input())
    cmd = input()

    try:
        print(MATH_OP[cmd](a, b))
    except ZeroDivisionError:
        print("Division by 0!")


if __name__ == "__main__":
    main()
