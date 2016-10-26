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
    for u, v in reader:
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


def find_min_cover(graph, max_match):
    # def build_orgraph():
    #     orgraph = [[] for _ in range(len(graph) - 2)]
    #     for u, v in max_match:
    unmatch_v = set(range(1, len(graph) // 2))
    unmatch_v = unmatch_v.difference(set(x[0] for x in max_match))
    visited = [False for _ in range(len(graph) - 2)]
    print(unmatch_v)

    return []


def main():
    reader = (tuple(map(int, line.split())) for line in sys.stdin)
    v_1, v_2, e = next(reader)
    graph, inp = build_graph(v_1, v_2, e, reader)
    max_match = find_max_match(graph)
    # print(inp, end="")
    find_min_cover(graph, max_match)


if __name__ == "__main__":
    main()
