#!/usr/bin/env python3
# coding=utf-8

import sys


def ReadGraph(num_vert, num_edges, reader):
    graph = {v: [] for v in range(1, num_vert + 1)}

    for _ in range(num_edges):
        u, v = next(reader)
        graph[u].append(v)
        graph[v].append(u)

    return graph


def conn_comp_count(graph):
    visited = [False for _ in range(len(graph))]
    conn_comp_dfs = 0

    for vertice in graph:
        if not visited[vertice - 1]:
            dfs(graph, vertice, visited)
            conn_comp_dfs += 1

    return conn_comp_dfs


def dfs(graph, u, visited):
    queue = [u]

    while len(queue) > 0:
        cur_v = queue.pop()
        visited[cur_v - 1] = True

        for v in graph[cur_v]:
            if not visited[v - 1]:
                visited[v - 1] = True
                queue.append(v)


def main():
    reader = (tuple(map(int, line.split())) for line in sys.stdin)
    n, m = next(reader)
    graph = ReadGraph(n, m, reader)
    print(conn_comp_count(graph))


if __name__ == "__main__":
    main()
