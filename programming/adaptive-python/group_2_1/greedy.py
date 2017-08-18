#!/usr/bin/env python3
# coding=utf-8
"""
Greedy

Little Johnny eats fruits from his grandma's basket.
There are fruits with different mass in this basket.
Little Johnny can pick up not more than K ounces.
Each fruit weights not more than K ounces. At a time,
he chooses a few of the most heavy fruits, which he
can pick up simultaneously, bites a half of each of
them and puts what is left back into the basket. If
the fruit weights odd number of ounces, he bites off
its half, rounded up to the nearest whole number. He
completely eats those fruits, which weight 1 ounce.
Find the number of attempts Little Johnny needs in order
to eat all fruits in the basket.

Write your heap storage class, which implements
priority queue.

Input data format. Integer n – the number of fruits, and
the line with integer masses of fruits separated by space.
Then in the separate line - the "lifting capacity".

Output data format. A non-negative number – the number
of attempts to the basket.

Sample Input:
3
1 2 2
2
Sample Output:
4
"""

import sys
import math
import operator


class PriorityQueue:
    def __init__(self, *args, comp=operator.lt):
        self.size = len(args)
        self.heap = [x for x in args]
        self.comp = comp
        self.__heapify()

    def __repr__(self):
        return repr(self.heap)

    def __len__(self):
        return self.size

    def max(self):
        return self.heap[0] if self.size > 0 else None

    def push(self, x):
        self.heap.append(x)
        self.__sift_up(self.size)
        self.size += 1

    def pop(self):
        if self.size > 0:
            val = self.heap[0]
            self.heap[0] = self.heap[self.size - 1]
            self.heap.pop()
            self.size -= 1
            self.__sift_down(0)

            return val

        return None

    def __heapify(self):
        i = (self.size - 1) // 2

        while i >= 0:
            self.__sift_down(i)
            i -= 1

    def __sift_down(self, index):
        while 2 * index + 1 < self.size:
            left = 2 * index + 1
            right = left + 1
            j = left

            if (right < self.size and
                    self.comp(self.heap[right], self.heap[left])):
                j = right

            if not self.comp(self.heap[j], self.heap[index]):
                break

            self.heap[index], self.heap[j] = \
                self.heap[j], self.heap[index]

            index = j

    def __sift_up(self, index):
        p_index = (index - 1) // 2

        while index > 0 and self.comp(self.heap[index], self.heap[p_index]):
            self.heap[index], self.heap[p_index] = \
                self.heap[p_index], self.heap[index]
            p_index = (index - 1) // 2


def test():
    pq1 = PriorityQueue(3, 4, 1, 5)
    assert pq1.pop() == 1
    assert pq1.pop() == 3
    assert pq1.pop() == 4
    assert pq1.pop() == 5
    pq2 = PriorityQueue(3, 4, 1, 5, comp=operator.gt)
    assert pq2.pop() == 5
    assert pq2.pop() == 4
    assert pq2.pop() == 3
    assert pq2.pop() == 1


def calc_bites(fruits_weight, bite_cap):
    pq = PriorityQueue(*fruits_weight, comp=operator.gt)
    bites_counter = 0

    while len(pq) > 0:
        cur_cap = 0
        to_eat = []

        while len(pq) > 0 and cur_cap <= bite_cap:
            if cur_cap + pq.max() > bite_cap:
                break

            cur_cap += pq.max()
            to_eat.append(pq.pop())

        for i in to_eat:
            if i > 1:
                pq.push(math.floor(i / 2))

        bites_counter += 1

    return bites_counter


def main():
    reader = (tuple(map(int, line.split())) for line in sys.stdin)
    fruits_q, *empty = next(reader)
    fruits_weight = next(reader)
    bite_cap, *empty = next(reader)

    print(calc_bites(fruits_weight, bite_cap))


if __name__ == "__main__":
    main()
