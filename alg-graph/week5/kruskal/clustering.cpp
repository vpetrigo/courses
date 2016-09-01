#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <tuple>
#include "disjoint_set.hpp"

using TPoint = std::pair<int, int>;
using TVertice = unsigned int;
using TDist = double;
using TEdge = std::tuple<TVertice, TVertice, double>;

std::vector<TPoint> read_coords(unsigned int n);
std::vector<TEdge> create_edge_list(const std::vector<TPoint>& coords);
double calculate_length(const TPoint& p1, const TPoint& p2);
// find distance 'd' that all cluster would have at least between each other
double make_clusters(const unsigned n, const unsigned k,
                     const std::vector<TEdge>& edges_list);

int main() {
  unsigned n, k;

  std::cin >> n;

  auto coords = read_coords(n);
  auto edges_list = create_edge_list(coords);

  std::cin >> k;
  // it says that we have number of nodes more than number of clusters
  assert(n >= k);
  std::cout << std::fixed << std::setprecision(9)
            << make_clusters(n, k, edges_list) << std::endl;

  return 0;
}

std::vector<TPoint> read_coords(unsigned int n) {
  std::vector<TPoint> coords(n);
  int x, y;

  for (auto& el : coords) {
    std::cin >> x >> y;
    el.first = x;
    el.second = y;
  }

  return coords;
}

std::vector<TEdge> create_edge_list(const std::vector<TPoint>& coords) {
  std::vector<TEdge> edges_list;
  const auto coords_q = coords.size();
  // for now we have a full graph
  const auto edges_q = coords_q * (coords_q - 1) / 2;
  edges_list.reserve(edges_q);

  for (std::size_t i = 0; i < coords_q; ++i) {
    for (std::size_t j = i + 1; j < coords_q; ++j) {
      edges_list.emplace_back(
          std::make_tuple(i, j, calculate_length(coords[i], coords[j])));
    }
  }
  assert(edges_list.size() == edges_q);

  return edges_list;
}

double calculate_length(const TPoint& p1, const TPoint& p2) {
  auto diff1 = p1.first - p2.first;
  auto diff2 = p1.second - p2.second;

  return std::sqrt(diff1 * diff1 + diff2 * diff2);
}

double make_clusters(const unsigned n, const unsigned k,
                     const std::vector<TEdge>& edges_list) {
  DisjointSet clusters{n};
  std::vector<TEdge> sorted_edges(edges_list);
  // at first we have dozen of nodes not related to any cluster
  std::size_t clusters_count = n;
  auto it = std::begin(sorted_edges);

  std::sort(std::begin(sorted_edges), std::end(sorted_edges),
            [](const TEdge& a, const TEdge& b) {
              return std::get<2>(a) < std::get<2>(b);
            });

  while (clusters_count != k - 1 && it != std::end(edges_list)) {
    auto u = std::get<0>(*it);
    auto v = std::get<1>(*it);

    if (clusters.Find(u) != clusters.Find(v)) {
      --clusters_count;
      clusters.Unite(u, v);
    }

    ++it;
  }

  // return distance from the previous edge as it violate the necessary
  // clusters number
  return std::get<2>(*(it - 1));
}
