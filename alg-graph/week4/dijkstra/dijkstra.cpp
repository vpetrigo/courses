#include <iostream>
#include <queue>
#include <algorithm>
#include <functional>

using WeightType = unsigned;
using VerticeType = std::pair<unsigned, WeightType>;
using DistanceType = unsigned long;
using DistanceCont = std::vector<DistanceType>;
using DistanceCont = std::vector<DistanceType>;
using PrevCont = std::vector<VerticeType::first_type>;
using GraphRepr = std::vector<std::vector<VerticeType>>;
using HeapType = std::pair<DistanceType, VerticeType::first_type>;
using DijkstraQueue = std::priority_queue<HeapType, std::vector<HeapType>, std::greater<HeapType>>;

GraphRepr create_graph(int v, int e);
bool RelaxEdge(const unsigned u, const unsigned v,
               const WeightType w, DistanceCont &dist,
               PrevCont &prev);
WeightType Dijkstra(const GraphRepr &graph, const unsigned start_node,
                    const unsigned end_node);
void InitDijkstraConts(PrevCont &prev, DistanceCont &dist);
DijkstraQueue MakeDijkstraQueue(const DistanceCont &dist);

int main() {
  int V, E;
  constexpr auto INF = std::numeric_limits<DistanceType>::max();
  constexpr auto NO_PATH = -1;

  std::cin >> V >> E;

  auto graph = create_graph(V, E);
  unsigned start, end;

  std::cin >> start >> end;

  auto result = Dijkstra(graph, start - 1, end - 1);
  if (result != INF) {
    std::cout << result;
  }
  else {
    std::cout << NO_PATH;
  }
  std::cout << std::endl;
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

bool RelaxEdge(const unsigned u, const unsigned v,
               const WeightType w, DistanceCont &dist,
               PrevCont &prev) {
  if (dist[v] > dist[u] + w) {
    dist[v] = dist[u] + w;
    prev[v] = u;
    // an edge was relaxed
    return true;
  }
  // an edge wasn't relaxed
  return false;
}

void InitDijkstraConts(PrevCont &prev, DistanceCont &dist) {
  constexpr auto INIT_VAL = std::numeric_limits<DistanceType>::max();
  std::fill(prev.begin(), prev.end(), INIT_VAL);
  std::fill(dist.begin(), dist.end(), INIT_VAL);
}

WeightType Dijkstra(const GraphRepr &graph, const unsigned start_node,
                    const unsigned end_node) {
  constexpr auto INF = std::numeric_limits<DistanceType>::max();
  PrevCont prev(graph.size());
  DistanceCont dist(graph.size());
  InitDijkstraConts(prev, dist);

  dist[start_node] = 0;
  DijkstraQueue queue = MakeDijkstraQueue(dist);

  while (!queue.empty()) {
    auto u_vertice = queue.top();
    queue.pop();

    for (const auto &edge : graph[u_vertice.second]) {
      const auto u_vertice_num = u_vertice.second;
      const auto v_vertice_num = edge.first;
      const auto v_vertice_weight = edge.second;
      // if there is at least one vertice with known distance
      // try to relax an edge between them
      if (!(dist[u_vertice_num] == INF && dist[v_vertice_num] == INF) &&
          RelaxEdge(u_vertice_num, v_vertice_num,
                    v_vertice_weight, dist, prev)) {
        queue.push(std::make_pair(dist[v_vertice_num], v_vertice_num));
      }
    }
  }

  return dist[end_node];
}

DijkstraQueue MakeDijkstraQueue(const DistanceCont &dist) {
  DijkstraQueue queue;

  for (std::size_t i = 0; i < dist.size(); ++i) {
    queue.push(std::make_pair(dist[i], i));
  }

  return queue;
}
