#!/usr/bin/env python3
# coding=utf-8


def main():
    seq = list(map(int, input().split()))
    print(*tuple(reversed(seq[:-1])))


if __name__ == "__main__":
    main()
