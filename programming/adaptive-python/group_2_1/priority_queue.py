#!/usr/bin/env python3
# coding=utf-8

import queue


def main():
    n = int(input())
    q = queue.PriorityQueue()

    for _ in range(n):
        cmd = input().split()

        if cmd[0] == "Insert":
            q.put(-int(cmd[1]))
        else:
            print(-q.get())


if __name__ == "__main__":
    main()
