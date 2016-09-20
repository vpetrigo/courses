#!/usr/bin/env python3
# coding=utf-8

import sys
import math


def main():
    tables = [math.ceil(int(x) / 2) for x in sys.stdin]
    print(sum(tables))


if __name__ == "__main__":
    main()