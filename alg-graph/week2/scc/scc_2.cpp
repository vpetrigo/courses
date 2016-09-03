#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using Vertice_t = unsigned;
using Graph_t = std::vector<std::vector<Vertice_t>>;
using VisitTime_t = std::pair<unsigned, unsigned>;
using GraphVisitTime_t = std::vector<VisitTime_t>;

enum class VerticeStatus {
  UNVISITED,
  PROCESSING,
  VISITED
};

using VerticesStatus_t = std::vector<VerticeStatus>;
using ProcStack_t = std::stack<Vertice_t>; 

Graph_t create_graph(const unsigned vertice_q, const unsigned edges_q);
Graph_t create_reverse_graph(const Graph_t& normal_graph);
GraphVisitTime_t dfs(const Graph_t& graph);
void explore(const Graph_t& graph, const Vertice_t v, VerticesStatus_t& visited,
             GraphVisitTime_t *times = nullptr, unsigned *time = nullptr);
GraphVisitTime_t get_postorder(const GraphVisitTime_t& v_time);
unsigned count_scc(const Graph_t& graph, GraphVisitTime_t& post_time);

int main() {
  unsigned vertice_q, edge_q;

  std::cin >> vertice_q >> edge_q;
  // obtain edges from the input
  auto graph = create_graph(vertice_q, edge_q);
  // reverse the graph for further processing
  auto rev_graph = create_reverse_graph(graph);
  // visit all verticies and find out pre- and post-times
  auto visit_time = dfs(rev_graph);
  // for counting SCC only post-time is needed
  auto post_time = get_postorder(visit_time); 
  std::cout << count_scc(graph, post_time) << std::endl;

  return 0;
}

Graph_t create_graph(const unsigned vertice_q, const unsigned edges_q) {
  Graph_t graph(vertice_q);

  for (std::size_t i = 0; i < edges_q; ++i) {
    Vertice_t u, v;

    std::cin >> u >> v;
    graph[u - 1].emplace_back(v - 1);
  }

  return graph;
}

Graph_t create_reverse_graph(const Graph_t& normal_graph) {
  const auto graph_size = normal_graph.size();
  Graph_t reverse_graph(graph_size);

  for (std::size_t i = 0; i < graph_size; ++i) {
    // for each vertice reverse edges
    for (const auto& neighbour : normal_graph[i]) {
      reverse_graph[neighbour].emplace_back(i);
    }
  }

  return reverse_graph;
}

GraphVisitTime_t dfs(const Graph_t& graph) {
  const auto g_size = graph.size();
  GraphVisitTime_t times(g_size, std::make_pair(0, 0));
  VerticesStatus_t visited(g_size, VerticeStatus::UNVISITED);
  unsigned cur_time = 0;

  for (std::size_t i = 0; i < g_size; ++i) {
    if (visited[i] == VerticeStatus::UNVISITED) {
      explore(graph, i, visited, &times, &cur_time);
    }
  }

  return times; 
}

void explore(const Graph_t& graph, const Vertice_t v, VerticesStatus_t& visited,
             GraphVisitTime_t *times, unsigned *time) {
  visited[v] = VerticeStatus::PROCESSING;
  if (times && time) {
    (*times)[v].first = ++*time;
  }

  for (const auto& neighbour : graph[v]) {
    if (visited[neighbour] == VerticeStatus::UNVISITED) {
      explore(graph, neighbour, visited, times, time);
    }
  }
  visited[v] = VerticeStatus::VISITED;
  if (times && time) {
    (*times)[v].second = ++*time;
  }
}

GraphVisitTime_t get_postorder(const GraphVisitTime_t& v_time) {
  GraphVisitTime_t post_times(v_time.size());
  Vertice_t v{0};

  std::transform(v_time.cbegin(), v_time.cend(), post_times.begin(), [&v](const VisitTime_t& t) {
    return std::make_pair(t.second, v++);
  });

  return post_times;
}

unsigned count_scc(const Graph_t& graph, GraphVisitTime_t& post_time) {
  unsigned conn_comp = 0;
  VerticesStatus_t visited(graph.size(), VerticeStatus::UNVISITED);
  std::sort(post_time.begin(), post_time.end(), std::greater<VisitTime_t>{});

  for (const auto& v : post_time) {
    if (visited[v.second] == VerticeStatus::UNVISITED) {
      ++conn_comp;
      explore(graph, v.second, visited);
    }
  }

  return conn_comp;
}