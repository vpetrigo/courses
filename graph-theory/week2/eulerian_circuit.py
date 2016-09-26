#!/usr/bin/env python3
# coding=utf-8

import sys
import copy


def ReadGraph(num_v, num_e, reader):
    graph = {v: [] for v in range(1, num_v + 1)}

    for _ in range(num_e):
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


def euler_candidate(graph):
    odd_degrees = tuple(filter(lambda n: n % 2 != 0,
                               [len(graph[v]) for v in graph]))

    if any(odd_degrees) or conn_comp_count(graph) != 1:
        return False

    return True


def restore_eulerian_circuit(graph):
    def remove_edge(g, u, v):
        g[u].remove(v)
        g[v].remove(u)

    def visit(g, v):
        for n in graph[v]:
            remove_edge(graph, v, n)
            visit(graph, n)

        cycle.append(v)

    graph_copy = copy.deepcopy(graph)
    start_edge = next(iter(graph))
    cycle = []
    visit(graph_copy, start_edge)
    cycle = list(reversed(cycle))
    cycle.pop()

    return cycle


def main():
    reader = (tuple(map(int, line.split())) for line in sys.stdin)
    n, m = next(reader)
    graph = ReadGraph(n, m, reader)

    if euler_candidate(graph):
        print(*restore_eulerian_circuit(graph))
    else:
        print("NONE")


if __name__ == "__main__":
    main()
