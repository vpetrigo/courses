#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <iterator>
#include <queue>
#include <set>

using Vertice_t = unsigned;
using Weight_t = long long;
using Dist_t = Weight_t;
using Edge_t = std::tuple<Vertice_t, Vertice_t, Weight_t>;
using Adjacency_t = std::pair<Vertice_t, Weight_t>;
using Graph_t = std::vector<std::vector<Adjacency_t>>;

constexpr auto INF = std::numeric_limits<Dist_t>::max();
// function for reading edges list from stdin
std::vector<Edge_t> ReadEdgeList(const unsigned num_e);
// BellmanFord algorithm modification that returns the
// list of nodes that are on a negative cycle/cycles;
// for other nodes it sets up correct distance values
std::vector<Vertice_t> BellmanFord(const std::vector<Edge_t>& edges,
                                   const Vertice_t num_v,
                                   const Vertice_t source,
                                   std::vector<Dist_t>& distance);
// relax edge between vertices u and v
bool RelaxEdge(const Vertice_t u, const Vertice_t v, const Weight_t w,
               std::vector<Dist_t>& dist);
// create graph (adjacency list) according to the edges list
Graph_t CreateGraph(const std::vector<Edge_t>& edges_list, const unsigned num_v);
// breadth first search algorithm modification that returns all nodes
// reachable from the source vertice
std::vector<Vertice_t> BreadthFirstSearch(const Graph_t& graph,
                                          const Vertice_t source,
                                          std::vector<bool>& visited);

int main() {
  unsigned n, m;
  std::cin >> n >> m;
  std::vector<Edge_t> edges_list{ReadEdgeList(m)};
  std::vector<Dist_t> distance(n, INF);
  Vertice_t source;
  std::cin >> source;
  auto vertices_on_neg_cycle = BellmanFord(edges_list, n, source - 1,
                                           distance);
  const auto graph = CreateGraph(edges_list, n);
  std::set<Vertice_t> vert_with_inf_dist;
  std::vector<bool> visited(n, false);

  for (const auto& vert : vertices_on_neg_cycle) {
    auto neg_reachable_vertices = BreadthFirstSearch(graph, vert,
                                                     visited);
    std::move(neg_reachable_vertices.begin(),
              neg_reachable_vertices.end(),
              std::inserter(vert_with_inf_dist, vert_with_inf_dist.begin()));
  }

  for (std::size_t i = 0; i < n; ++i) {
    if (vert_with_inf_dist.find(i) != vert_with_inf_dist.cend()) {
      std::cout << '-';
    }
    else {
      if (distance[i] != INF) {
        std::cout << distance[i];
      }
      else {
        std::cout << '*' << std::endl;
      }
    }

    std::cout << std::endl;
  }

  return 0;
}

std::vector<Edge_t> ReadEdgeList(const unsigned num_e) {
  std::vector<Edge_t> edge_list(num_e);

  for (auto &edge : edge_list) {
    Vertice_t u, v;
    Weight_t w;

    std::cin >> u >> v >> w;
    edge = std::make_tuple(u - 1, v - 1, w);
  }

  return edge_list;
}

std::vector<Vertice_t> BellmanFord(const std::vector<Edge_t>& edges,
                                   const Vertice_t num_v,
                                   const Vertice_t source,
                                   std::vector<Dist_t>& distance) {
  bool changed = true;
  // storage for keeping nodes that lay on a negative cycle
  std::vector<Vertice_t> on_neg_cycle;

  on_neg_cycle.reserve(num_v);
  distance[source] = 0;

  for (std::size_t i = 0; i < num_v + 1 && changed; ++i) {
    changed = false;
    Vertice_t v, u;
    Weight_t w;

    for (const auto& edge : edges) {
      std::tie(u, v, w) = edge;

      if (distance[u] != INF && RelaxEdge(u, v, w, distance)) {
        changed = true;

        if (i == num_v) {
          on_neg_cycle.emplace_back(v);
        }
      }
    }
  }

  on_neg_cycle.shrink_to_fit();

  return on_neg_cycle;
}

bool RelaxEdge(const Vertice_t u, const Vertice_t v, const Weight_t w,
               std::vector<Dist_t>& dist) {
  const auto new_dist = dist[u] + w;

  if (dist[v] > new_dist) {
    dist[v] = new_dist;

    return true;
  }

  return false;
}

Graph_t CreateGraph(const std::vector<Edge_t>& edges_list, const unsigned num_v) {
  Graph_t graph(num_v);

  for (const auto& edge : edges_list) {
    Vertice_t u, v;
    Weight_t w;

    std::tie(u, v, w) = edge;
    graph[u].emplace_back(std::make_pair(v, w));
  }

  return graph;
}

std::vector<Vertice_t> BreadthFirstSearch(const Graph_t& graph,
                                          const Vertice_t source,
                                          std::vector<bool>& visited) {
  std::vector<Vertice_t> reachable_from_neg;

  if (!visited[source]) {
    std::queue<Vertice_t> queue;

    queue.push(source);
    visited[source] = true;

    while (!queue.empty()) {
      auto cur_v = queue.front();
      queue.pop();
      reachable_from_neg.push_back(cur_v);

      for (const auto& neighbour : graph[cur_v]) {
        if (!visited[neighbour.first]) {
          visited[neighbour.first] = true;
          queue.push(neighbour.first);
        }
      }
    }
  }

  return reachable_from_neg;
}
