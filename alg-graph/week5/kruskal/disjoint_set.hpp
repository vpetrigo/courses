#ifndef ALG_GRAPH_DISJOINT_SET_HPP
#define ALG_GRAPH_DISJOINT_SET_HPP

#include <vector>
#include <cinttypes>

class DisjointSet {
 public:
  using value_type = uint64_t;

  DisjointSet(value_type size);

  ~DisjointSet() = default;

  void MakeSet(value_type element);
  value_type Find(value_type element);
  void Unite(value_type x, value_type y);
 private:
  std::vector<value_type> parent;
};

#endif // ALG_GRAPH_DISJOINT_SET_HPP
