#include <cstdlib>
#include <ctime>
#include "disjoint_set.hpp"

DisjointSet::DisjointSet(value_type size) : parent(size) {
  std::srand(std::time(nullptr));

  for (std::size_t i = 0; i < parent.size(); ++i) {
    MakeSet(i);
  }
}

void DisjointSet::MakeSet(value_type element) {
  if (element < parent.size()) {
    parent[element] = element;
  }
}

DisjointSet::value_type DisjointSet::Find(value_type element) {
  if (parent[element] == element) {
    return element;
  }

  return parent[element] = Find(parent[element]);;
}

void DisjointSet::Unite(value_type x, value_type y) {
  // find parent
  x = Find(x);
  y = Find(y);

  if (std::rand() % 2 == 0) {
    std::swap(x, y);
  }

  parent[x] = y;
}
