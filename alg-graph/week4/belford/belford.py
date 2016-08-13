#!/usr/bin/env python3
# coding=utf-8


import sys
import math
import heapq


def ReadEdges(reader):
    return next(reader)


def CreateGraph(num_v, num_e, reader):
    """
    Create graph with @num_v vertices with @num_e edges.
    Read it via the @reader generator
    """
    graph = dict(zip((vertice for vertice in range(1, num_v + 1)),
                     [[] for _ in range(num_v)]))

    for _ in range(num_e):
        (u, v, w) = ReadEdges(reader)
        graph[u].append((v, w))

    return graph


def BellmanFordNegCycle(graph, start_node):
    dist = [math.inf for _ in graph]
    dist[start_node - 1] = 0
    queue = [(dist[i - 1], i) for i in range(1, len(graph) + 1)]
    heapq.heapify(queue)
    counter = 0

    while len(queue) > 0:
        cur_node = heapq.heappop(queue)

        if (cur_node[0] == math.inf):
            break

        u = cur_node[1]
        for v_info in graph[u]:
            edge_weight = v_info[1]
            v = v_info[0]

            if (RelaxEdge(u - 1, v - 1, edge_weight, dist)):
                heapq.heappush(queue, (dist[v - 1], v))
                if counter == len(graph) + 1:
                    return True

        counter += 1

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

    for start_node in range(1, v + 1):
        if (BellmanFordNegCycle(graph, start_node)):
            print(1)
            break
    else:
        print(0)


if __name__ == "__main__":
    main()
