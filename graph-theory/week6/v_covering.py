#!/usr/bin/env python3
# coding = utf-8

import sys


def build_graph(v_1, v_2, e, reader):
    graph = [[] for _ in range(v_1 + v_2 + 2)]

    # add helper x, y vertices
    # x connected with all vertices from X part
    x = 0
    # y connected with all vertices from Y part
    y = v_1 + v_2 + 1

    for i in range(x + 1, v_1 + 1):
        graph[x].append(i)
        graph[i].append(x)

    for i in range(v_1 + 1, y):
        graph[y].append(i)
        graph[i].append(y)

    inp = " ".join(str(x) for x in (v_1, v_2, e)) + "\n"
    # read the rest edges in bipartite graph
    for _ in range(e):
        u, v = next(reader)
        inp += " ".join(str(x) for x in (u, v)) + "\n"
        graph[u + 1].append(v + 1)
        graph[v + 1].append(u + 1)

    return graph, inp


def find_max_match(graph):
    def dfs(s, t):
        """
        Find the path from a source to a sink
        """
        if s == t:
            return [s]

        visited[s] = True

        for n in graph[s]:
            if not visited[n]:
                new_path = dfs(n, t)

                if new_path:
                    return [s] + new_path

        return None

    visited = [False for _ in range(len(graph))]
    source = 0
    sink = len(graph) - 1
    max_match = []

    while True:
        path = dfs(source, sink)

        if not path:
            break

        visited[source] = False
        visited[sink] = False
        max_match.append((path[1], path[2]))

    return max_match


def find_min_cover(v_1, graph, max_match):
    def build_orgraph():
        orgraph = [[] for _ in range(len(graph) - 2)]

        for i in range(1, v_1 + 1):
            for n in graph[i]:
                if n != 0 and n != len(graph) - 1:
                    orgraph[i - 1].append(n - 1)

        for u, v in max_match:
            orgraph[v - 1].append(u - 1)
            orgraph[u - 1].remove(v - 1)

        return orgraph

    def dfs(source):
        visited[source] = True

        for n in orgraph[source]:
            if not visited[n]:
                dfs(n)

    unmatch_v = tuple(x - 1 for x in range(1, v_1 + 1)
                      if all(x != y[0] for y in max_match))
    print(unmatch_v)
    orgraph = build_orgraph()
    visited = [False for _ in range(len(graph) - 2)]
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
    graph, inp = build_graph(v_1, v_2, e, reader)
    max_match = find_max_match(graph)
    print(max_match)
    # print(inp, end="")
    print(*find_min_cover(v_1, graph, max_match))


if __name__ == "__main__":
    main()
