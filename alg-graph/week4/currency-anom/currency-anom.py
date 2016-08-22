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


def BellmanFord(num_v, graph, start_node):
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

    print("Dist: ", dist)

    return inf_loop


def BreadthFirstSearch(graph, start_node):
    pass


def main():
    reader = (tuple(map(int, line.split())) for line in sys.stdin)
    num_v, num_e = next(reader)
    graph = CreateGraph(num_e, reader)
    s_node, *none = next(reader)
    inf_loop_verticies = BellmanFord(num_v, graph, s_node - 1)

if __name__ == "__main__":
    main()
