#!/usr/bin/env python3
# coding=utf-8


def main():
    n = int(input())
    snowflake = [["." for _ in range(n)] for _ in range(n)]
    mid = n // 2

    for i in range(n):
        snowflake[i][mid] = "*"
        snowflake[mid][i] = "*"
        snowflake[i][i] = "*"
        snowflake[i][n - i - 1] = "*"

    print("\n".join(" ".join(line) for line in snowflake))


if __name__ == "__main__":
    main()
