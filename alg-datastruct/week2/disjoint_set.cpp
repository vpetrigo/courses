#include "disjoint_set.hpp"

#include <iostream>
#include <utility>

int main() {
  std::size_t n_tables, n_queries;

  std::cin >> n_tables >> n_queries;

  DB_TableDisjointSet dset{n_tables};

  for (std::size_t i = 0; i < n_tables; ++i) {
    std::size_t n_entries;

    std::cin >> n_entries;
    dset.MakeSet(std::make_pair(i, n_entries));
  }

  std::size_t dest, src;

  for (std::size_t i = 0; i < n_queries; ++i) {
    std::cin >> dest >> src;
    std::cout << dset.Union(dest - 1, src - 1) << std::endl;
  }

  return 0;
}