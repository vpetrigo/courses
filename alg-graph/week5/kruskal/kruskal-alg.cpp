#include <iostream>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <ctime>

class DisjointSet {
 public:
  using value_type = uint64_t;

  DisjointSet(value_type size) : parent(size) {
    std::srand(std::time(nullptr));

    for (std::size_t i = 0; i < parent.size(); ++i) {
      MakeSet(i);
    }
  }

  ~DisjointSet() = default;

  void MakeSet(value_type element) {
    if (element < parent.size()) {
      parent[element] = element;
    }
  }

  value_type Find(value_type element) {
    if (parent[element] == element) {
      return element;
    }

    return parent[element] = Find(parent[element]);
  }

  void Unite(value_type x, value_type y) {
    // find parent
    x = Find(x);
    y = Find(y);

    if (std::rand() % 2 == 0) {
      std::swap(x, y);
    }

    parent[x] = y;
  }
 private:
  std::vector<value_type> parent;
};

int main() {
  DisjointSet s{5};

  s.Unite(0, 1);
  s.Unite(2, 3);
  s.Unite(3, 4);

  auto first_set = s.Find(1);
  auto second_set = s.Find(4);
  std::cout << first_set << std::endl;
  std::cout << second_set << std::endl;

  return 0;
}
