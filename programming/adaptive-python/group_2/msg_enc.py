#!/usr/bin/env python3
# coding=utf-8


def main():
    message = input().strip()
    print(" ".join((str(ord(ch)) for ch in message)))


if __name__ == "__main__":
    main()
