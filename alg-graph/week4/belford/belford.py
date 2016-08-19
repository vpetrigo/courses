#!/usr/bin/env python3
# coding=utf-8


import sys
import math


def ReadEdges(reader):
    return next(reader)


def CreateGraph(num_v, num_e, reader):
    """
    Create graph with @num_v vertices with @num_e edges.
    Read it via the @reader generator
    For Bellman-Ford algorithm it is enough to store only edges
    """
    edges = tuple(ReadEdges(reader) for _ in range(num_e))

    return edges


def BellmanFordNegCycle(graph, num_v):
    dist = [0 for _ in range(num_v)]

    for it in range(num_v + 1):
        for edge in graph:
            u, v, w = edge
            if (RelaxEdge(u - 1, v - 1, w, dist)):
                if it == num_v:
                    return True

    return False


def RelaxEdge(u, v, edge_w, dist):
    new_dist = dist[u] + edge_w

    if dist[v] > new_dist:
        dist[v] = new_dist
        return True

    return False


def main():
    reader = (tuple(map(int, line.split())) for line in sys.stdin)
    v, e = next(reader)
    graph = CreateGraph(v, e, reader)

    if (BellmanFordNegCycle(graph, v)):
        print(1)
    else:
        print(0)


if __name__ == "__main__":
    main()
