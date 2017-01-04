#!/usr/bin/env python3
# coding=utf-8


import heapq
import collections


class PriorityQueue:
    def __init__(self, queue, compare=lambda x: x):
        self.compare = compare
        self.queue = [(self.compare(item), count, item) for count, item in enumerate(queue)]
        self.counter = len(self.queue)
        heapq.heapify(self.queue)

    def __len__(self):
        return len(self.queue)

    def push(self, item):
        heapq.heappush(self.queue, (self.compare(item), self.counter, item))
        self.counter += 1

    def pop(self):
        return heapq.heappop(self.queue)[-1]


def build_tree(string):
    frequencies = collections.defaultdict(int)

    for ch in string:
        frequencies[ch] += 1

    pq = PriorityQueue((Leaf(ch, frequencies[ch]) for ch in frequencies), lambda x: x.get_frequency())

    while len(pq) > 1:
        first, second = pq.pop(), pq.pop()
        pq.push(Node(first, second))

    root = pq.pop()

    if isinstance(root, Leaf):
        root = Node(root)
    # return root of a Huffman binary tree
    return root


class HuffmanEncoder:
    """
    class for performing Huffman encoding
    """
    def __init__(self):
        """
        constructor defines:
        @root node the Huffman encoding binary tree
        @code binary code for each symbol in an input
        """
        self.root = None
        self.code = {}

    def encode(self, string):
        self.root = build_tree(string)
        self.root.walk(self.code)
        encoded_string = "".join(self.code[ch] for ch in string)

        return encoded_string

    def get_code(self):
        return self.code


class Node:
    def __init__(self, left=None, right=None):
        self.left = left
        self.right = right
        fl = left.freq if left else 0
        fr = right.freq if right else 0
        self.freq = fl + fr

    def get_frequency(self):
        return self.freq

    def walk(self, code, acc=""):
        if self.left:
            self.left.walk(code, acc + "0")
        if self.right:
            self.right.walk(code, acc + "1")


class Leaf:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq

    def get_frequency(self):
        return self.freq

    def walk(self, code, acc):
        code[self.char] = acc or "0"


def main():
    string = input()
    henc = HuffmanEncoder()
    encoded_string = henc.encode(string)
    code = henc.get_code()

    print(len(code.items()), len(encoded_string))
    for ch in sorted(code):
        print("{}: {}".format(ch, code[ch]))

    print(encoded_string)


if __name__ == "__main__":
    main()
