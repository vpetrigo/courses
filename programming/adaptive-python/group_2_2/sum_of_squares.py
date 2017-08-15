#!/usr/bin/env python3


import sys


def main():
    reader = (int(num) for num in sys.stdin)
    nums = []
    
    while len(nums) == 0 or sum(nums) != 0:
        nums.append(next(reader))

    print(sum([x ** 2 for x in nums]))


if __name__ == "__main__":
    main()
