#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using VerticeType = unsigned;
using GraphRepr = std::vector<std::vector<VerticeType>>;
using PrevRepr = std::vector<VerticeType>;
using DistRepr = std::vector<int>;
using VisitedVertices = std::vector<bool>;

enum class VerticeColor : unsigned short { BLACK, WHITE };

using VerticeColors = std::vector<VerticeColor>;

GraphRepr create_graph(int v, int e);
// modified BFS for checking whether a graph is bipartite or not
bool bfs(const GraphRepr &graph, VerticeType from, VisitedVertices &visited);
void PrintShortestPath(const PrevRepr &prev, VerticeType from, VerticeType to);
void ColorVertice(const VerticeType &v, const VerticeType &prev_v,
                  VerticeColors &colors);

int main() {
  int n, m;
  // read number of vertices and edges
  std::cin >> n >> m;

  auto graph = create_graph(n, m);
  VisitedVertices visited(n);
  bool bipartite = true;

  for (std::size_t i = 0; i < n && !visited[i]; ++i) {
    if (!visited[i] && !bfs(graph, i, visited)) {
      bipartite = false;
    }
  }

  if (bipartite) {
    std::cout << "1";
  }
  else {
    std::cout << "0";
  }
  std::cout << std::endl;

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

bool bfs(const GraphRepr &graph, VerticeType from, VisitedVertices &visited) {
  std::queue<VerticeType> queue;
  DistRepr dist(graph.size(), -1);
  VerticeColors colors(graph.size(), VerticeColor::BLACK);
  PrevRepr prev(graph.size());
  constexpr auto INIT_LEVEL = 0U;
  constexpr auto INIT_COLOR = VerticeColor::WHITE;

  queue.push(from);
  prev[from] = from;
  dist[from] = INIT_LEVEL;
  colors[from] = INIT_COLOR;

  while (!queue.empty()) {
    auto cur_node = queue.front();
    visited[cur_node] = true;
    queue.pop();

    for (const auto &e : graph[cur_node]) {
      if (dist[e] == -1) {
        queue.push(e);
        prev[e] = cur_node;
        dist[e] = dist[cur_node] + 1;
        ColorVertice(e, cur_node, colors);
      }
      else if (colors[e] == colors[cur_node]) {
        // have same colored node on both ends of an edge
        return false;
      }
    }
  }

  return true;
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

  for (const auto &e : path) {
    to_output += std::to_string(e + 1);
    to_output += " -> ";
  }
  to_output += "end";

  std::cout << to_output << std::endl;
}

void ColorVertice(const VerticeType &v, const VerticeType &prev_v,
                  VerticeColors &colors) {
  colors[v] = (colors[prev_v] == VerticeColor::BLACK) ? VerticeColor::WHITE
                                                      : VerticeColor::BLACK;
}
