#!/usr/bin/env python3
# coding=utf8

import sys


# naive adjacency list
def build_adj_list(reader, n, m):
    adj_list = [[] for i in range(n)]

    for _ in range(m):
        v1, v2 = next(reader)
        adj_list[v1 - 1].append(v2 - 1)
        adj_list[v2 - 1].append(v1 - 1)

    return adj_list


def dfs(adj_list):
    conn_comp = 0
    n = len(adj_list)
    visited = [False for _ in range(n)]

    for i in range(n):
        if not visited[i]:
            explore(adj_list, i, visited)
            conn_comp += 1

    return conn_comp


def explore(adj_list, u, visited):
    visited[u] = True

    for w in adj_list[u]:
        if not visited[w]:
            explore(adj_list, w, visited)


def test():
    pass


def main():
    reader = (tuple(map(int, line.split())) for line in sys.stdin)
    n, m = next(reader)
    adj_list = build_adj_list(reader, n, m)

    ans = dfs(adj_list)
    print(ans)

if __name__ == "__main__":
    main()

