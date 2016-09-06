#include <cstddef>
#include <algorithm>
#include <functional>
#include <iterator>
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


// fill adjacent list with input values
void fill_vector(const int m, GraphRepr& graph) {
  for (std::size_t i = 0; i < m; ++i) {
    int u, v;

    std::cin >> u >> v;
    graph[u - 1].emplace_back(v - 1);
  }
}

void explore(const GraphRepr &graph, int vertice, std::vector<VerticeStatus>& visited,
             std::vector<int> &pre, std::vector<int> &post, int& time) {
  VerticeStack process_stack;

  process_stack.push(std::make_pair(vertice, graph[vertice].begin()));
  pre[vertice] = time++;

  while (!process_stack.empty()) {
    auto& processing_vertice = process_stack.top();
    visited[processing_vertice.first] = VerticeStatus::processing;
    // if the current vertice's adjacent list is empty or
    // we reach the end of that list mark that vertice as visited and exit
    if (graph[processing_vertice.first].empty() ||
        processing_vertice.second == std::end(graph[processing_vertice.first])) {
      visited[processing_vertice.first] = VerticeStatus::visited;
      post[processing_vertice.first] = time++;
      process_stack.pop();
    }
    else {
      // look up for unvisited verticies
      // we might find already visited verticies
      if (visited[*processing_vertice.second] ==
          VerticeStatus::unvisited) {
        process_stack.emplace(std::make_pair(
            *processing_vertice.second, std::begin(graph[*processing_vertice.second])));
        pre[*processing_vertice.second] = time++;
      }

      processing_vertice.second = std::next(processing_vertice.second);
    }
  }
}
void dfs(const GraphRepr& graph, std::vector<int>& pre, std::vector<int>& post) {
  std::vector<VerticeStatus> visited(graph.size(), VerticeStatus::unvisited);
  int time = 1;

  for (std::size_t i = 0; i < graph.size(); ++i) {
    if (visited[i] != VerticeStatus::visited) {
      explore(graph, i, visited, pre, post, time);
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

  std::transform(postorder.cbegin(), postorder.cend(), out.begin(), [&vertice_index](const int& posttime) {
    return std::make_pair(posttime, vertice_index++);
  });

  return out;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  GraphRepr graph(n);

  fill_vector(m, graph);

  auto post_o = topological_sort(graph);
  auto ans = get_vertice_index(post_o);

  std::sort(ans.begin(), ans.end(), std::greater<std::pair<int, int>> ());
  for (const auto& elem : ans) {
    std::cout << elem.second << ' ';
  }
  std::cout << std::endl;

  return 0;
}
