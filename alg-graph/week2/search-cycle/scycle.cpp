#include <cassert>
#include <cstddef>
#include <iostream>
#include <vector>
#include <stack>
#include <iterator>
#include <utility>

enum class VerticeStatus { unvisited, processing, visited };

// alias for representing a graph as an adjacency list
using GraphRepr = typename std::vector<std::vector<int>>;
// alias for storage of vertices processing status
using Visited = typename std::vector<VerticeStatus>;

template <typename CIt>
using GraphTraverseStack = typename std::stack<std::pair<const int, CIt>>;

void FillGraph(const int e, GraphRepr& graph) {
  int u, v;
  for (size_t i = 0; i < e; ++i) {
    std::cin >> u >> v;
    graph[u - 1].push_back(v - 1);
  }
}

bool Explore(const GraphRepr& graph, const int vertice,
             Visited* visited_list) {
  // put the @vertice into the stack
  GraphTraverseStack<typename GraphRepr::value_type::const_iterator>
      processing_stack;

  processing_stack.emplace(std::make_pair(vertice, graph[vertice].begin()));
  (*visited_list)[vertice] = VerticeStatus::processing;

  while (!processing_stack.empty()) {
    auto& current_vertice = processing_stack.top();

    if (graph[current_vertice.first].empty() ||
        current_vertice.second == std::end(graph[current_vertice.first])) {
      // there are no ways from the current vertice
      (*visited_list)[current_vertice.first] = VerticeStatus::visited;
      processing_stack.pop();
    } else {
      // if we found a vertice that was already being processed
      // we found a cycle
      if ((*visited_list)[*current_vertice.second] ==
          VerticeStatus::processing) {
        return true;
      }

      if ((*visited_list)[*current_vertice.second] ==
          VerticeStatus::unvisited) {
        // add vertice for further processing
        processing_stack.emplace(std::make_pair(
            *current_vertice.second, graph[*current_vertice.second].cbegin()));
        (*visited_list)[*current_vertice.second] = VerticeStatus::processing;
      }

      current_vertice.second = std::next(current_vertice.second);
    }
  }

  return false;
}

bool SearchCycle(const GraphRepr& graph) {
  Visited vlist(graph.size(), VerticeStatus::unvisited);

  for (std::size_t i = 0; i < graph.size(); ++i) {
    if (vlist[i] == VerticeStatus::unvisited && Explore(graph, i, &vlist)) {
      return true;
    }
  }

  return false;
}

int main() {
  // number of verticies and edges in a graph
  int v, e;
  std::cin >> v >> e;
  GraphRepr graph(v);

  FillGraph(e, graph);
  std::cout << SearchCycle(graph) << std::endl;

  return 0;
}
