#ifndef _DISJOINT_SET_HPP_
#define _DISJOINT_SET_HPP_

#include <algorithm>
#include <vector>

class DB_TableDisjointSet {
 public:
  // table contains id (pair.first) and number of entries (pair.second)
  using value_type = std::pair<std::size_t, std::size_t>;

  explicit DB_TableDisjointSet(std::size_t size) : parent_{}, max_entries_{0} {
    parent_.resize(size);
  }

  void MakeSet(const value_type& element) {
    parent_[element.first] = element;
    max_entries_ = std::max(element.second, max_entries_);
  }

  value_type& Find(std::size_t element_id) {
    if (element_id != parent_[element_id].first) {
      parent_[element_id] = Find(parent_[element_id].first);
    }

    return parent_[element_id];
  }

  std::size_t Union(std::size_t dest, std::size_t source) {
    auto& dest_parent = Find(dest);
    auto& source_parent = Find(source);

    if (dest_parent == source_parent) {
      return max_entries_;
    }

    dest_parent.second += source_parent.second;
    max_entries_ = std::max(dest_parent.second, max_entries_);
    parent_[dest_parent.first] = dest_parent;
    parent_[source_parent.first] = dest_parent;

    return max_entries_;
  }
 private:
  std::vector<value_type> parent_;
  std::size_t max_entries_;
};

#endif // _DISJOINT_SET_HPP_
