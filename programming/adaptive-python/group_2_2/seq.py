#!/usr/bin/env python3


def main():
    n = int(input())
    # sum of sequence 1, -0.5, 0.25, -0.125 ...
    print(sum([(-1 / 2) ** i for i in range(n)]))


if __name__ == "__main__":
    main()
