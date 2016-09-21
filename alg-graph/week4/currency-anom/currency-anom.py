#!/usr/bin/env python3
# coding=utf-8

import sys
import math


class Inf:
    def __lt__(self, other):
        return False

    def __gt__(self, other):
        if isinstance(other, Inf):
            return False

        return True

    def __le__(self, other):
        return self.__lt__(other) or self.__eq__(other)

    def __ge__(self, other):
        return self.__gt__(other) or self.__eq__(other)

    def __eq__(self, other):
        if isinstance(other, Inf):
            return True

        return False

    def __ne__(self, other):
        return not self.__eq__(other)

    def __add__(self, other):
        return self

    def __sub__(self, other):
        return self

    def __repr__(self):
        return "inf"


inf = Inf()


def ReadEdges(num_edges, reader):
    return tuple(next(reader) for _ in range(num_edges))


def RelaxEdge(u, v, w, dist):
    new_dist = dist[u] + w

    if dist[v] > new_dist:
        dist[v] = new_dist

        return True

    return False


def BellmanFord(num_v, edges, start_node):
    inf_loop = []
    dist = [inf for _ in range(num_v)]
    dist[start_node] = 0

    for it in range(num_v + 1):
        # flag for detecting whether we changed smth on the
        # current algorithm iteration or not
        changed = False
        for edge in edges:
            u, v, w = edge

            if RelaxEdge(u - 1, v - 1, w, dist):
                changed = True

                if it == num_v:
                    inf_loop.append(v)

        if not changed:
            break

    return dist, inf_loop


def BreadthFirstSearch(graph, start_node, visited):
    no_route_nodes = []

    if not visited[start_node - 1]:
        queue = [start_node]
        visited[start_node - 1] = True

        while len(queue) > 0:
            cur_vertice = queue.pop(0)
            no_route_nodes.append(cur_vertice)

            for vertice in graph[cur_vertice]:
                if not visited[vertice[0] - 1]:
                    visited[vertice[0] - 1] = True
                    queue.append(vertice[0])

    return no_route_nodes


def CreateAdjacencyListGraph(num_v, edges):
    graph = {v: [] for v in range(1, num_v + 1)}

    for u, v, w in edges:
        graph[u].append((v, w))

    return graph


def GetAnswer(edges, num_v, dist, inf_loop_verticies):
    unreachable_verticies = set()
    graph = CreateAdjacencyListGraph(num_v, edges)
    visited = [False for _ in range(num_v)]

    for v in inf_loop_verticies:
        unreachable_verticies.update(BreadthFirstSearch(graph, v,
                                                        visited))
    answer = []

    for it in range(1, num_v + 1):
        if it in unreachable_verticies:
            answer.append("-")
        else:
            if dist[it - 1] != inf:
                answer.append(dist[it - 1])
            else:
                answer.append("*")

    return answer


def main():
    reader = (tuple(map(int, line.split())) for line in sys.stdin)
    num_v, num_e = next(reader)
    edges = ReadEdges(num_e, reader)
    s_node, *none = next(reader)
    dist, inf_loop_verticies = BellmanFord(num_v, edges, s_node - 1)

    print("\n".join(str(el) for el in GetAnswer(edges, num_v,
                                                dist, inf_loop_verticies)))


if __name__ == "__main__":
    main()
