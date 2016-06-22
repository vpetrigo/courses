#include <cstddef>
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>
#include <stack>

using GraphRepr = std::vector<std::vector<int>>;
using VerticeStack = std::stack<std::pair<int, GraphRepr::value_type::const_iterator>>;

enum class VerticeStatus {
  unvisited,
  processing,
  visited
};

void fill_vector(const int m, GraphRepr& graph) {
  for (std::size_t i = 0; i < m; ++i) {
    int u, v;

    std::cin >> u >> v;
    graph[u - 1].emplace_back(v - 1);
  }
}

void explore(const GraphRepr &graph, int vertice, std::vector<bool> visited,
             std::vector<int> &pre, std::vector<int> &post) {
  VerticeStack process_stack{{vertice, graph[vertice].cbegin()}};
  int pre_time = 0;
  int post_time = 0;

  if (pre.empty() || post.empty()) {
    pre_time = 1;
    post_time = pre_time;
  }
  else {
    pre_time = pre.back();
    post_time = post.back();
  }

  while (!process_stack.empty()) {
    auto processing_vertice = process_stack.top();

    pre[processing_vertice.first] = pre_time++;
    if (!visited[processing_vertice]) {
      for (auto e : graph[processing_vertice]) {
        process_stack.emplace(e);
      }
    }

    visited[vertice] = true;
  }
}
void dfs(const GraphRepr& graph, std::vector<int>& pre, std::vector<int>& post) {
  std::vector<bool> visited(graph.size(), false);

  for (std::size_t i = 0; i < graph.size(); ++i) {
    if (!visited[i]) {
      explore(graph, i, visited, pre, post);
    }
  }
}

std::vector<int> topological_sort(const GraphRepr& graph) {
  std::vector<int> preorder(graph.size());
  std::vector<int> postorder(graph.size());

  dfs(graph, preorder, postorder);
  return postorder;
}

std::vector<std::pair<int, int>> get_vertice_index(const std::vector<int>& postorder) {
  // make pairs (postorder time, vertice index)
  std::vector<std::pair<int, int>> out(postorder.size());
  std::size_t vertice_index = 1;

  std::transform(postorder.cbegin(), postorder.cend(), out.begin(), [](const int& posttime) {
    return std::make_pair(posttime, vertice_index++);
  });
}

int main() {
  int n, m;
  std::cin >> n >> m;
  GraphRepr graph(n);
  auto post_o = topological_sort(graph);
  auto ans = get_vertice_index(post_o);

  std::sort(ans.cbegin(), ans.cend(), std::greater<std::pair<int, int>> ());
  for (const auto& elem : ans) {
    std::cout << elem.second << ' ';
  }
  std::cout << std::endl;

  return 0;
}
