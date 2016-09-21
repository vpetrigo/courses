#!/usr/bin/env python3
# coding=utf-8

import sys
import heapq


INF = 1e9


def main():
    reader = (tuple(map(int, line.split())) for line in sys.stdin)
    n, m = next(reader)
    graph = CreateGraph(n, m, reader)
    u, v = next(reader)
    dist = Dijkstra(graph, u - 1, v - 1)

    if dist != INF:
        print(dist)
    else:
        print(-1)


def CreateGraph(num_v, num_e, reader):
    """
    Read edges from the reader (it might be attached to stdin or file) in
    format 'U V W'
    """
    graph = [[] for _ in range(num_v)]

    for _ in range(num_e):
        u, v, w = next(reader)
        graph[u - 1].append((v - 1, w))

    return graph


def Dijkstra(graph, u, v):
    dist = [INF for _ in range(len(graph))]
    dist[u] = 0
    queue = [(dist[i], i) for i in range(len(graph))]
    heapq.heapify(queue)

    while len(queue) > 0:
        proc_u_dist, proc_u = heapq.heappop(queue)

        if proc_u_dist <= dist[proc_u]:
            for neighbour in graph[proc_u]:
                neighbour_v, neighbour_w = neighbour

                if RelaxEdge(proc_u, neighbour_v, neighbour_w, dist):
                    heapq.heappush(queue, (dist[neighbour_v],
                                           neighbour_v))

    return dist[v]


def RelaxEdge(u, v, w, dist):
    new_dist = dist[u] + w

    if dist[v] > new_dist:
        dist[v] = new_dist

        return True

    return False


if __name__ == "__main__":
    main()
