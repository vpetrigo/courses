#include <iostream>
#include <cassert>
#include <cmath>
#include <tuple>
#include "disjoint_set.hpp"

using TPoint = std::pair<int, int>;
using TVertice = unsigned int;
using TDist = double;
using TEdge = std::tuple<TVertice, TVertice, double>;

std::vector<TPoint> read_coords(unsigned int n);
std::vector<TEdge> create_edge_list(const std::vector<TPoint>& coords);
double calculate_length(const TPoint& p1, const TPoint& p2);

int main() {
  unsigned n;

  std::cin >> n;

  auto coords = read_coords(n);

  create_edge_list(coords);

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
