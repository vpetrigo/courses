#!/usr/bin/env python3
# coding=utf-8


def print_cube_path(a, b):
    def inverse(a, i):
        return "0" if a[i] == "1" else "1"

    k = len(a)
    cube_visited = {}
    cube_visited[a] = True

    for i in range(k):
        print(a, end=" ")
        neighbour = a[:i] + inverse(a, i) +  a[i + 1:]
        print(neighbour, end=" ")
        for j in range(k):
            n = (i + j + 1) % k

            if neighbour[n] != b[n]:
                neighbour = (neighbour[:n] + inverse(neighbour, n) +
                                neighbour[n + 1:])
                print(neighbour, end=" ")

        print()


def main():
    a, b = input().split()
    assert len(a) == len(b)
    print_cube_path(a, b)


if __name__ == "__main__":
    main()
