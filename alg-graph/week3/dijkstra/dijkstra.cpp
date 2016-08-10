#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <utility>
#include <limits>

using WeightType = unsigned;
using VerticeType = std::pair<unsigned, WeightType>;
using DistanceType = long;
using DistanceCont = std::vector<DistanceType>;
using DistanceCont = std::vector<DistanceType>;
using PrevCont = std::vector<VerticeType>;
using GraphRepr = std::vector<std::vector<VerticeType>>;
using HeapType = std::pair<DistanceType, VerticeType>;
using DijkstraQueue = std::priority_queue<HeapType>;

GraphRepr create_graph(int v, int e);
bool RelaxEdge(const VerticeType& v, const VerticeType& u,
               const WeightType w, DistanceCont &dist,
               PrevCont &prev);
WeightType Dijkstra(const GraphRepr &graph, const unsigned start_node,
              const unsigned end_node);
void InitDijkstraConts(PrevCont &prev, DistanceCont &dist);
DijkstraQueue MakeDijkstraQueue(DistanceCont &dist);

int main() {
  int V, E;

  std::cin >> V >> E;

  auto graph = create_graph(V, E);
  unsigned start, end;

  std::cin >> start >> end;

  std::cout << Dijkstra(graph, start, end) << std::endl;
}

GraphRepr create_graph(int v, int e) {
  // create a new directed graph by reading edges
  // from standard input (v <-> u) and an edge weight w
  GraphRepr g(v);

  while (e--) {
    unsigned v, u, w;

    std::cin >> v >> u >> w;
    g[v - 1].emplace_back(std::make_pair(u - 1, w));
  }

  return g;
}

bool RelaxEdge(const VerticeType& v, const VerticeType& u,
               const WeightType w, DistanceCont &dist,
               PrevCont &prev) {
  if (dist[v.first] > dist[u.first] + w) {
    dist[v.first] = dist[u.first] + w;
    prev[v.first] = u;
    // an edge was relaxed
    return true;
  }
  // an edge wasn't relaxed
  return false;
}

void InitDijkstraConts(PrevCont &prev, DistanceCont &dist) {
  constexpr auto INIT_VAL = std::numeric_limits<long>::infinity();
  std::fill(prev.begin(), prev.end(), INIT_VAL);
  std::fill(dist.begin(), dist.end(), INIT_VAL);
}

WeightType Dijkstra(const GraphRepr &graph, const unsigned start_node,
              const unsigned end_node) {
  PrevCont prev(graph.size());
  DistanceCont dist(graph.size());
  InitDijkstraConts(prev, dist);

  dist[start_node] = 0;
  DijkstraQueue queue = MakeDijkstraQueue(dist);

  while (!queue.empty()) {
    auto u_vertice = queue.top();
    queue.pop();

    for (const auto &e : graph[u_vertice.second.first]) {
      const auto u_vertice_num = u_vertice.second;
      const auto v_vertice_num = e.first;
      const auto v_vertice_weight = e.second;

      if (RelaxEdge(u_vertice_num, v_vertice_num,
                    v_vertice_weight, dist, prev)) {
        queue.push(std::make_pair(dist[u_vertice_num], u_vertice_num));
      }
    }
  }

  return dist[end_node];
}

DijkstraQueue MakeDijkstraQueue(DistanceCont &dist) {
  DijkstraQueue queue;

  for (std::size_t i = 0; i < dist.size(); ++i) {
    queue.push(std::make_pair(dist[i], i));
  }

  return queue;
}
