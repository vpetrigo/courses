#!/usr/bin/env python3
# coding=utf-8

import sys

MAX_CAPACITY = 50


def is_forward_path(u, v, graph):
    return graph[u][v] is not None


def build_graph(num_v, num_e, reader):
    graph = [[None] * num_v for _ in range(num_v)]

    for _ in range(num_e):
        u, v, w = next(reader)
        graph[u][v] = w

    return graph


def build_residual_graph(graph):
    residual_graph = [[None] * len(graph) for _ in range(len(graph))]

    for u, row in enumerate(graph):
        for v, capacity in enumerate(row):
            if capacity is not None:
                if residual_graph[u][v] is None:
                    residual_graph[u][v] = 0
                if residual_graph[v][u] is None:
                    residual_graph[v][u] = 0

                residual_graph[u][v] += capacity

    return residual_graph


def find_max_flow(path, residual_graph):
    edges = [(path[i], path[i + 1]) for i in range(len(path) - 1)]
    # bottleneck capacity of a path
    b_capacity = MAX_CAPACITY

    for u, v in edges:
        b_capacity = min(b_capacity, residual_graph[u][v])

    return b_capacity


def max_flow(source, sink, graph):
    def dfs(s, t):
        if s == t:
            return [t]

        visited[s] = True
        neighbours = tuple(i for i, w in enumerate(residual_graph[s])
                           if w is not None and w != 0)

        for n in neighbours:
            if not visited[n]:
                forward_path = is_forward_path(s, n, graph)

                if forward_path:
                    eflow = graph[s][n] - residual_graph[s][n]
                else:
                    eflow = residual_graph[s][n]

                if (forward_path and eflow < graph[s][n] or
                        not forward_path and eflow > 0):
                    new_path = dfs(n, t)

                    if new_path:
                        return [s] + new_path

        return None

    def update_flow(p, m_flow):
        edges = [(p[i], p[i + 1]) for i in range(len(p) - 1)]

        for u, v in edges:
            residual_graph[u][v] -= m_flow
            residual_graph[v][u] += m_flow

    residual_graph = build_residual_graph(graph)
    const_visited = [False for _ in range(len(graph))]
    visited = const_visited[:]
    path = dfs(source, sink)
    graph_max_flow = 0

    while path:
        path_max_flow = find_max_flow(path, residual_graph)
        update_flow(path, path_max_flow)
        graph_max_flow += path_max_flow
        visited = const_visited[:]
        path = dfs(source, sink)

    return graph_max_flow


def main():
    reader = (tuple(map(int, line.split())) for line in sys.stdin)
    V, E = next(reader)
    graph = build_graph(V, E, reader)
    s, t = 0, V - 1
    print(max_flow(s, t, graph))


if __name__ == "__main__":
    main()
