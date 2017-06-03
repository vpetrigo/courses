#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using VerticeType = unsigned;
using GraphRepr = std::vector<std::vector<VerticeType>>;
using PrevRepr = std::vector<VerticeType>;
using DistRepr = std::vector<int>;

GraphRepr create_graph(int v, int e);
DistRepr bfs(const GraphRepr &graph, VerticeType from, VerticeType to);
void PrintShortestPath(const PrevRepr &prev, VerticeType from, VerticeType to);

int main() {
  int n, m;
  // read number of vertices and edges
  std::cin >> n >> m;

  auto graph = create_graph(n, m);
  VerticeType from, to;
  std::cin >> from >> to;
  
  auto result = bfs(graph, from - 1, to - 1);

  std::cout << result[to - 1] << std::endl;

  return 0;
}

GraphRepr create_graph(int v, int e) {
  // create a new graph by reading edges
  // from standard input (v <-> u)
  GraphRepr g(v);

  while (e--) {
    VerticeType v, u;

    std::cin >> v >> u;
    g[v - 1].push_back(u - 1);
    g[u - 1].push_back(v - 1);
  }

  return g;
}

DistRepr bfs(const GraphRepr &graph, VerticeType from, VerticeType to) {
  std::queue<VerticeType> queue;
  DistRepr dist(graph.size(), -1);
  PrevRepr prev(graph.size());
  constexpr auto INIT_LEVEL = 0U;

  queue.push(from);
  prev[from] = from;
  dist[from] = INIT_LEVEL;

  while (!queue.empty()) {
    auto cur_node = queue.front();
    queue.pop();

    for (const auto &e : graph[cur_node]) {
      if (dist[e] == -1) {
        queue.push(e);
        prev[e] = cur_node;
        dist[e] = dist[cur_node] + 1;
      }
    }
  }

  // if (dist[to] != -1) {
  //   PrintShortestPath(prev, from, to);
  // }

  return dist;
}

void PrintShortestPath(const PrevRepr &prev, VerticeType from, VerticeType to) {
  std::vector<VerticeType> path;
  VerticeType cur_node = to;

  while (cur_node != from) {
    path.push_back(cur_node);
    cur_node = prev[cur_node];
  }
  path.push_back(from);

  std::reverse(path.begin(), path.end());
  std::string to_output;

  for (const auto& e : path) {
    to_output += std::to_string(e + 1);
    to_output += " -> ";
  }
  to_output += "end";

  std::cout << to_output << std::endl;
}
