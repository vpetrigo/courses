#!/usr/bin/env python3


import sys
import itertools


def main():
    reader = (int(line) for line in sys.stdin)
    
    for num in filter(lambda x: x >= 10, itertools.takewhile(lambda y: y <= 100, reader)):
        print(num)


if __name__ == "__main__":
    main()
