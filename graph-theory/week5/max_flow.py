#!/usr/bin/env python3
# coding=utf-8

import collections
import sys


def build_graph(n, m, reader):
    graph = [[] for i in range(n)]

    for i in range(m):
        u, v, w = next(reader)
        graph[u].append((v, w))

    return graph


def max_flow(source: vertice, sink: vertise, graph):
    def dfs(s, t):
        visited[s] = True

        if s == t:
            return True

        for n, c in graph[s]:
            if not visited[n] and flow_value[s][n] <= c:
                flow_value[s][n] += c
                flow_value[n][s] -= c
                dfs(n, t)

        return False

    flow_value = [[0 for _ in range(len(graph))] for _ in range(len(graph))]
    visited = [False for _ in range(len(graph))]

    return 0


def main():
    reader = (tuple(map(int, line.split())) for line in sys.stdin)
    n_v, n_e = next(reader)
    print(build_graph(n_v, n_e, reader))
    source = 0
    sink = n_v - 1


if __name__ == "__main__":
    main()
