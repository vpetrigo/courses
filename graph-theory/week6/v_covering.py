#!/usr/bin/env python3
# coding = utf-8

import sys


def build_graph(v_1, v_2, e, reader):
    graph = [[] for _ in range(v_1 + v_2)]
    print(v_1, v_2, e)

    for _ in range(e):
        u, v = next(reader)
        print(u, v)
        graph[u].append(v + 1)
        graph[v].append(u + 1)

    return graph


def build_residual_graph(l_part, graph):
    # + 2 as we add two more vertice S and T
    # S connected with all vertex from L part
    # T connected with all vertex from R part
    g_len = len(graph) + 2
    residual_graph = [[None] * g_len for _ in range(g_len)]
    s = 0
    t = g_len - 1

    for i in range(1, l_part + 1):
        residual_graph[s][i] = 1
        residual_graph[i][s] = 0

    for i in range(l_part + 1, g_len - 1):
        residual_graph[i][t] = 1
        residual_graph[t][i] = 0

    for u in range(l_part):
        for v in graph[u]:
            residual_graph[u + 1][v] = 1
            residual_graph[v][u + 1] = 0

    return residual_graph


def is_forward_path(u, v, graph, l_part):
    return u <= l_part and v in graph[u]


def find_max_match(l_part, graph):
    """
    @graph is the original bipartite graph
    @l_part is the size of left part of BP graph
    """
    _FLOW = 1

    def dfs(s, t):
        """
        Find the path from a source to a sink
        """
        if s == t:
            return [s]

        visited[s] = True
        neighbours = tuple(i for i, w in enumerate(residual_graph[s])
                           if w is not None and w != 0)

        for n in neighbours:
            if not visited[n]:
                if (s < n and _FLOW - residual_graph[s][n] < _FLOW or
                        s > n and residual_graph[s][n] > 0):
                        new_path = dfs(n, t)

                        if new_path:
                            return [s] + new_path

        return None

    def update_residual(path):
        edges = [(path[i], path[i + 1]) for i in range(len(path) - 1)]

        for u, v in edges:
            residual_graph[u][v] -= _FLOW
            residual_graph[v][u] += _FLOW

    def get_matching():
        matching = []
        for i in range(1, l_part + 1):
            pair = [i for i, f in enumerate(residual_graph[i][1:-1], 1)
                    if f == 0]

            if pair:
                matching.append((i, pair.pop()))

        return matching

    residual_graph = build_residual_graph(l_part, graph)
    source = 0
    sink = len(residual_graph) - 1

    while True:
        # here while we are able to find a path and increase a flow
        # do it and update residual graph
        visited = [False for _ in range(len(residual_graph))]
        path = dfs(source, sink)

        if not path:
            break
        else:
            update_residual(path)

    return get_matching()


def find_min_cover(v_1, graph, max_match):
    def build_orgraph():
        orgraph = [[] for _ in range(g_len)]

        for i in range(v_1 + 1):
            for n in graph[i]:
                orgraph[i].append(n - 1)

        for u, v in max_match:
            orgraph[v - 1].append(u - 1)
            orgraph[u - 1].remove(v - 1)

        return orgraph

    def dfs(source):
        visited[source] = True

        for n in orgraph[source]:
            if not visited[n]:
                dfs(n)

    g_len = len(graph)
    unmatch_v = tuple(x - 1 for x in range(1, v_1 + 1)
                      if all(x != y[0] for y in max_match))

    orgraph = build_orgraph()
    visited = [False for _ in range(len(graph))]
    min_cover = []

    for v in unmatch_v:
        dfs(v)

    for u, v in max_match:
        if not visited[u - 1]:
            min_cover.append(u - 1)
        if visited[v - 1]:
            min_cover.append(v - 1)

    return sorted(min_cover)


def main():
    reader = (tuple(map(int, line.split())) for line in sys.stdin)
    v_1, v_2, e = next(reader)
    graph = build_graph(v_1, v_2, e, reader)
    max_match = find_max_match(v_1, graph)
    print(*find_min_cover(v_1, graph, max_match))


if __name__ == "__main__":
    main()
