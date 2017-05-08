#include "disjoint_set_rank.hpp"

#include <iostream>

int main()
{
  std::size_t n, e, d;
  bool success{true};

  std::cin >> n >> e >> d;

  DisjointSet<std::size_t> ds{n};

  for (std::size_t i = 0; i < n; ++i) {
    ds.MakeSet(i);
  }

  std::size_t var1, var2;

  for (std::size_t i = 0; i < e; ++i) {
    std::cin >> var1 >> var2;
    ds.Union(var1 - 1, var2 - 1);
  }

  for (std::size_t i = 0; i < d; ++i) {
    std::cin >> var1 >> var2;

    if (ds.Find(var1 - 1) == ds.Find(var2 - 1)) {
      std::cout << 0 << std::endl;
      success = false;
      break;
    }
  }

  if (success) {
    std::cout << 1 << std::endl;
  }

  return 0;
}
