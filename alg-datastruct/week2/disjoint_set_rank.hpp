#ifndef _DISJOINT_SET_RANK_HPP_
#define _DISJOINT_SET_RANK_HPP_

#include <vector>

template <typename T>
class DisjointSet {
 public:
  explicit DisjointSet(std::size_t size)
  {
    parent_.resize(size);
    rank_.resize(size);
  }

  void MakeSet(const T& elem)
  {
    if (parent_[elem] != elem) {
      parent_[elem] = elem;
      rank_[elem] = 0;
    }
  }

  T Find(std::size_t elem_id)
  {
    if (parent_[elem_id] != elem_id) {
      parent_[elem_id] = Find(parent_[elem_id]);
    }

    return parent_[elem_id];
  }

  void Union(std::size_t i, std::size_t j)
  {
    auto i_parent = Find(i);
    auto j_parent = Find(j);

    if (i_parent != j_parent) {
      if (rank_[i_parent] > rank_[j_parent]) {
        parent_[j_parent] = i_parent;
      }
      else {
        parent_[i_parent] = j_parent;

        if (rank_[i_parent] == rank_[j_parent]) {
          ++rank_[j_parent];
        }
      }
    }
  }

 private:
  std::vector<T> parent_;
  std::vector<std::size_t> rank_;
};

#endif  // _DISJOINT_SET_RANK_HPP_
