#!/usr/bin/env python3
# coding=utf8

import sys

# naive adjacency list
def build_adj_list(reader, n):
    adj_list = [[] for i in range(n)]

    for v1, v2 in reader:
        adj_list[v1 - 1].append(v2 - 1)
        adj_list[v2 - 1].append(v1 - 1)

    return adj_list

def is_path_exists(adj_list, u, v):
    visited = [False for _ in range(len(adj_list))]

    explore(adj_list, u, visited)
    return visited[v]


def explore(adj_list, u, visited):
    visited[u] = True

    for w in adj_list[u]:
        if not visited[w]:
            explore(adj_list, w, visited)

def test():
    adj_list1 = [[], []]
    assert is_path_exists(adj_list1, 0, 1) == False
    adj_list2 = [[1], [0]]
    assert is_path_exists(adj_list2, 0, 1) == True
    adj_list3 = [[1, 2], [0], [0, 3], [2]]
    assert is_path_exists(adj_list3, 0, 3) == True


def main():
    reader = (tuple(map(int, line.split())) for line in sys.stdin)
    n, m = next(reader)
    u, v = next(reader)
    graph = build_adj_list(reader, n)

    ans = 1 if is_path_exists(graph, u - 1, v - 1) else 0
    print(ans)

if __name__ == "__main__":
    main()
    test()
