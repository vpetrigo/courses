#!/usr/bin/env python3
# coding=utf-8

import sys
import math


def CreateGraph(num_edges, reader):
    return tuple(next(reader) for _ in range(num_edges))


def RelaxEdge(u, v, w, dist):
    new_dist = dist[u] + w

    if dist[v] > new_dist:
        dist[v] = new_dist

        return True

    return False


def BellmanFord(num_v, edges, start_node):
    inf_loop = []
    dist = [math.inf for _ in range(num_v)]
    dist[start_node] = 0

    for it in range(num_v + 1):
        # flag for detecting whether we changed smth on the
        # current algorithm iteration or not
        changed = False
        for edge in graph:
            u, v, w = edge

            if RelaxEdge(u - 1, v - 1, w, dist):
                changed = True

                if it == num_v:
                    inf_loop.append(u)

        if not changed:
            break

    return dist, inf_loop


def BreadthFirstSearch(graph, start_node, visited):
    no_route_nodes = []

    if not visited[start_node]:
        queue = [start_node]
        visited[start_node - 1] = True
        no_route_nodes.append(start_node)

        while len(queue) > 0:
            cur_vertice = queue.pop(0)

            for vertice in graph[cur_vertice]:
                v, w = vertice
                if not visited[v - 1]:
                    visited[v - 1] = True
                    no_route_nodes.append(v)
                    queue.append(v)

    return no_route_nodes


def CreateAdjacencyListGraph(num_v, edges):
    graph = {v: [] for v in range(1, num_v + 1)}

    for u, v, w in edges:
        graph[u].append((v, w))

    return graph


def GetAnswer(edges, num_v, dist, inf_loop_verticies):
    unreachable_verticies = set()
    if len(inf_loop_verticies) > 0:
        graph = CreateAdjacencyListGraph(num_v, edges)
        visited = [False for _ in range(num_v)]

        for v in inf_loop_verticies:
            if not visited[v - 1]:
                unreachable_verticies.update(BreadthFirstSearch(graph, v,
                                                                visited))

    answer = []

    for it in range(1, num_v + 1):
        if it not in unreachable_verticies:
            if dist[it - 1] != math.inf:
                answer.append(dist[it - 1])
            else:
                answer.append("-")
        else:
            answer.append("*")

    return answer


def main():
    reader = (tuple(map(int, line.split())) for line in sys.stdin)
    num_v, num_e = next(reader)
    edges = CreateGraph(num_e, reader)
    s_node, *none = next(reader)
    dist, inf_loop_verticies = BellmanFord(num_v, edges, s_node - 1)

    print("\n".join(str(el) for el in GetAnswer(edges, num_v,
                                                dist, inf_loop_verticies)))


if __name__ == "__main__":
    main()
