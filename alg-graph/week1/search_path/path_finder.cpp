#include <iostream>
#include <vector>
#include <cstddef>

using Graph_t = typename std::vector<std::vector<unsigned short>>;
using Visited_t = typename std::vector<bool>;

void build_adj_list(Graph_t &graph, unsigned int input_size) {
  for (std::size_t i = 0; i < input_size; ++i) {
    unsigned int v1, v2;

    std::cin >> v1 >> v2;
    graph[v1 - 1].push_back(v2 - 1);
    graph[v2 - 1].push_back(v1 - 1);
  }
}

void explore(const Graph_t &graph, unsigned int v, Visited_t &visited) {
  visited[v] = true;

  for (const auto &w : graph[v]) {
    if (!visited[w]) {
      explore(graph, w, visited);
    }
  }
}

bool is_path_exists(const Graph_t &graph, unsigned int u, unsigned int v) {
  Visited_t visited(graph.size(), false);

  explore(graph, u - 1, visited);

  return visited[v - 1];
}

int main() {
  unsigned int n, m;
  unsigned int u, v;

  std::cin >> n >> m;
  std::cin >> u >> v;

  Graph_t graph_repr(n);

  build_adj_list(graph_repr, m);
  std::cout << is_path_exists(graph_repr, u, v) << std::endl;

  return 0;
}
