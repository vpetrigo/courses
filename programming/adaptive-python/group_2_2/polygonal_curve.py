#!/usr/bin/env python3
# coding=utf-8


import sys
import heapq


class MinHeap:
    def __init__(self):
        self.heap = []

    def push(self, x):
        a, b = x
        heapq.heappush(self.heap, x)

    def pop(self):
        return heapq.heappop(self.heap)

    def __len__(self):
        return len(self.heap)


def main():
    heap = MinHeap()
    n = int(input())
    reader = (tuple(map(int, line.split())) for line in sys.stdin)

    for point in reader:
        heap.push(point)

    while len(heap) > 0:
        print(*heap.pop())


if __name__ == "__main__":
    main()
