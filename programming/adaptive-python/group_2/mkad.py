#!/usr/bin/env python3
# coding=utf-8


def main():
    v = int(input())
    t = int(input())
    # task constant path that can be passed
    path = 109

    stop = (path + v * t % path) % path
    print(stop)


if __name__ == "__main__":
    main()
