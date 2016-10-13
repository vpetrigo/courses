#include <algorithm>
#include <iostream>
#include <iterator>
#include <set>
#include <unordered_map>
#include <vector>

using Graph_t = std::unordered_map<unsigned, std::vector<unsigned>>;
constexpr int max_val = 100001;

class Vertice {
 public:
  explicit constexpr Vertice(unsigned num)
      : num_{num}, visited_{false}, in_time_{0}, l_value_{0} {}

  bool is_visited() const { return visited_; }

  void visit() { visited_ = true; }

  void set_in_time(unsigned t) { in_time_ = t; }

  void set_l_value(unsigned l_value) { l_value_ = l_value; }

  const unsigned get_in_time() const { return in_time_; }

  const unsigned get_l_value() const { return l_value_; }

  const unsigned get_num() const { return num_; }

 private:
  unsigned num_;
  bool visited_;
  unsigned in_time_;
  unsigned l_value_;
};

Graph_t create_graph();
std::set<unsigned> count_cut_vertices(const Graph_t &graph);
void dfs_cut(Vertice &s, const Vertice &p, std::vector<Vertice> &v_list,
             const Graph_t &graph, unsigned &time, std::set<unsigned> &c_v);

int main() {
  auto graph = create_graph();
  auto answer = count_cut_vertices(graph);
  std::for_each(answer.cbegin(), answer.cend(),
                [](const unsigned &n) { std::cout << n << ' '; });
  std::cout << std::endl;

  return 0;
}

Graph_t create_graph() {
  Graph_t graph;
  unsigned u, v;

  while (std::cin >> u >> v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  return graph;
}

std::set<unsigned> count_cut_vertices(const Graph_t &graph) {
  std::vector<Vertice> vertices;
  std::transform(graph.cbegin(), graph.cend(), std::back_inserter(vertices),
                 [](const Graph_t::value_type &v) { return Vertice{v.first}; });
  std::sort(vertices.begin(), vertices.end(),
            [](const Vertice &a, const Vertice &b) {
              return a.get_num() < b.get_num();
            });

  unsigned time = 1;
  std::set<unsigned> cut_vertices;
  constexpr Vertice no_parent{max_val};

  dfs_cut(vertices.front(), no_parent, vertices, graph, time, cut_vertices);

  return cut_vertices;
}

void dfs_cut(Vertice &source, const Vertice &parent,
             std::vector<Vertice> &v_list, const Graph_t &graph, unsigned &time,
             std::set<unsigned> &c_v) {
  source.set_in_time(time);
  source.set_l_value(time);
  source.visit();
  ++time;
  unsigned children = 0;

  for (const auto &n : graph.at(source.get_num())) {
    // don't try to check parent node as it uses the same
    // edge
    if (n != parent.get_num()) {
      if (!v_list[n].is_visited()) {
        // descendant node
        dfs_cut(v_list[n], source, v_list, graph, time, c_v);
        source.set_l_value(
            std::min(source.get_l_value(), v_list[n].get_l_value()));

        if (v_list[n].get_l_value() >= source.get_in_time() &&
            parent.get_num() != max_val) {
          // a descendant node has l(n) >= k(source), so deleting of the source
          // vertice cause to increase of connected components number
          c_v.emplace(source.get_num());
        }
        ++children;
      }
      else {
        // ancestor node
        source.set_l_value(
            std::min(source.get_l_value(), v_list[n].get_in_time()));
      }
    }
  }

  if (parent.get_num() == max_val && children > 1) {
    c_v.emplace(source.get_num());
  }
}
