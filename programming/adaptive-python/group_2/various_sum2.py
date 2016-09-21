#!/usr/bin/env python3
# coding=utf-8


def subset_sum(seq, req_sum) -> int:
    seq_len = len(seq)
    subsum = [False for _ in range(req_sum)]
    subsum[0] = True

    for i in seq:
        for j in range(req_sum - 1, -1, -1):
            if subsum[j]:
                subsum[j + i] = True

    return subsum


def various_sum_count(seq) -> int:
    max_sum = sum(seq)
    s = subset_sum(seq, max_sum + 1)

    return s.count(True)


def test():
    assert various_sum_count([1, 2, 3]) == 7
    assert various_sum_count([1, 1, 1]) == 4


def main():
    N = int(input())
    seq = tuple(map(int, input().split()))

    print(various_sum_count(seq))


if __name__ == "__main__":
    test()
    main()
