#!/usr/bin/env python3
# coding=utf-8


def greedy_exchange(msum, money_set):
    exchange = []

    while msum > 0:
        for i in money_set:
            if i <= msum:
                exchange.append(i)
                msum -= i
                break

    return len(exchange)


def dp_exchange(msum, money_set):
    change = [i for i in range(msum + 1)]

    for c in range(1, msum + 1):
        for coin in money_set:
            if coin <= c:
                change[c] = min(change[c], 1 + change[c - coin])

    return change[msum]


def main():
    money_sum = int(input())
    money_set = tuple(map(int, input().split(",")))

    print(dp_exchange(money_sum, money_set))


if __name__ == "__main__":
    main()