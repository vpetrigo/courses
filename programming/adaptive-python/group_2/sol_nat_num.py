#!/usr/bin/env python3
# coding=utf-8


import math


# naive solution
def square_int(n):
    border = math.floor(math.sqrt(n))

    for i in range(border + 1):
        for j in range(i, border + 1):
            square_sum = i ** 2 + j ** 2
            if square_sum == n:
                return (i, j)

    return ()

def square_int_2(n):
    # x ^ 2 + y ^ 2 = N => x, y < sqrt(N)
    border = math.floor(math.sqrt(n))

    for x in range(border + 1):
        # y ^ 2
        x_2 = x ** 2
        y_2 = n - x_2

        y = math.sqrt(y_2)
        if y == int(y) and x_2 + y_2 == n:
            return (x, int(y))
    else:
        return ()


def main():
    n = int(input())
    ans = square_int_2(n)

    if len(ans) > 0:
        print("{0[0]} {0[1]}".format(ans))
    else:
        print("No solution")


if __name__ == "__main__":
    main()
