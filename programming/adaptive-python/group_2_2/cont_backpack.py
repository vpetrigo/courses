#!/usr/bin/env python3
# coding=utf-8

import sys


def items_cost(items, bp_capacity):
    items_by_cost = sorted(items, key=lambda e: e[0] / e[1], reverse=True)
    cur_weight = 0
    cur_cost = 0
    i = 0

    while i < len(items_by_cost):
        item = items_by_cost[i]

        if cur_weight + item[1] > bp_capacity:
            break

        cur_weight += item[1]
        cur_cost += item[0]
        i += 1

    if i != len(items_by_cost) and cur_weight < bp_capacity:
        cur_cost += (bp_capacity - cur_weight) * \
                    items_by_cost[i][0] / items_by_cost[i][1]

    return cur_cost


def main():
    reader = (tuple(map(int, line.split())) for line in sys.stdin)
    n, bp_w = next(reader)
    items = [next(reader) for _ in range(n)]
    print("{:.3f}".format(items_cost(items, bp_w)))


if __name__ == "__main__":
    main()
