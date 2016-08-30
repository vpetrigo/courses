#include <iostream>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <numeric>
#include <limits>
#include <queue>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <ctime>

using TVertice = unsigned int;
using TDist = double;
using Point = std::pair<int, int>;
using Edge = std::pair<TVertice, double>;
using Graph = std::vector<std::vector<Edge>>;
using TQueue = std::priority_queue<std::pair<TDist, TVertice>,
                                   std::vector<std::pair<TDist, TVertice>>,
                                   std::greater<std::pair<TDist, TVertice>>>;

constexpr auto INF = std::numeric_limits<TDist>::max();

void read_coords(unsigned int n, std::vector<Point>& coords);
Graph create_graph(const std::vector<Point>& coords);
double calculate_length(const Point& p1, const Point& p2);
double minimum_length_path(const Graph& graph);
TQueue init_queue(const std::vector<TDist>& dist);

int main() {
  unsigned int n = 0;
  std::vector<Point> coords;

  std::cin >> n;
  coords.resize(n);
  read_coords(n, coords);
  auto graph = create_graph(coords);
  std::cout << std::fixed <<
    std::setprecision(9) << minimum_length_path(graph) << std::endl;

  return 0;
}

void read_coords(unsigned int n, std::vector<Point>& coords) {
  assert(n == coords.size());
  int x, y;

  for (auto& el : coords) {
    std::cin >> x >> y;
    el = std::make_pair(x, y);
  }
}

Graph create_graph(const std::vector<Point>& coords) {
  // convert input coords into an undirected graph with weighted edges
  const auto points_q = coords.size();
  Graph g(points_q);

  for (std::size_t i = 0; i < points_q; ++i) {
    for (std::size_t j = i + 1; j < points_q; ++j) {
      // get distance between two points
      const auto dist = calculate_length(coords[i], coords[j]);

      g[i].emplace_back(std::make_pair(j, dist));
      g[j].emplace_back(std::make_pair(i, dist));
    }
  }

  return g;
}

double calculate_length(const Point& p1, const Point& p2) {
  auto diff1 = p1.first - p2.first;
  auto diff2 = p1.second - p2.second;

  return std::sqrt(diff1 * diff1 + diff2 * diff2);
}

double minimum_length_path(const Graph& graph) {
  std::srand(std::time(nullptr));
  const auto vertices_q = graph.size();
  auto rand_v = std::rand() % vertices_q;
  std::vector<TDist> dist(vertices_q, INF);
  dist[rand_v] = 0;
  TQueue queue = init_queue(dist);
  std::vector<bool> in_queue(vertices_q, true);

  while (!queue.empty()) {
    auto cur_vertice = queue.top();
    queue.pop();
    in_queue[cur_vertice.second] = false;

    for (const auto& neighbour : graph[cur_vertice.second]) {
      if (in_queue[neighbour.first] && dist[neighbour.first] > neighbour.second) {
        dist[neighbour.first] = neighbour.second;
        queue.emplace(std::make_pair(neighbour.second, neighbour.first));
      }
    }
  }

  auto result = std::accumulate(dist.cbegin(), dist.cend(), 0);

  return result;
}

TQueue init_queue(const std::vector<TDist>& dist) {
  TQueue q;

  for (std::size_t i = 0; i < dist.size(); ++i) {
    q.emplace(std::make_pair(dist[i], i));
  }

  return q;
}
