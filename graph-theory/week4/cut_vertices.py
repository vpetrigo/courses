#!/usr/bin/env python3
# coding=utf-8

import sys
import collections


def create_graph(reader):
    graph = collections.defaultdict(list)
    for (u, v) in reader:
        graph[u].append(v)
        graph[v].append(u)

    return graph


def find_cut_points(graph):
    def dfs(source, parent):
        nonlocal k_array_cnt
        visited[source] = True
        k_array[source] = l_array[source] = k_array_cnt
        k_array_cnt += 1
        children = 0

        for n in graph[source]:
            if n != parent:
                if not visited[n]:
                    visited[n] = True
                    dfs(n, source)
                    l_array[source] = min(l_array[source], l_array[n])
                    if l_array[n] >= k_array[source] and parent is not None:
                        cut_v.add(source)

                    children += 1
                else:
                    l_array[source] = min(l_array[source], k_array[n])

            if parent is None and children > 1:
                cut_v.add(source)

    s = next(iter(graph))
    graph_l = len(graph)
    visited = [False for _ in range(graph_l)]
    k_array = [-1 for i in range(graph_l)]
    k_array_cnt = 1
    l_array = [-1 for _ in range(graph_l)]
    l_array[s] = 1
    cut_v = set()
    dfs(s, None)

    return cut_v


def main():
    reader = (tuple(map(int, line.split()) for line in sys.stdin))
    graph = create_graph(reader)
    print(*find_cut_points(graph))


if __name__ == "__main__":
    main()
