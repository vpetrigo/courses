#ifndef _COURSES_CHECK_TREE_STRICT_HPP_
#define _COURSES_CHECK_TREE_STRICT_HPP_

#include <tuple>
#include <vector>

using KeyDepth = std::pair<long long, std::size_t>;
// TreeNode for storing in an array or vector
// 0 element - key
// 1 element - left child index
// 2 element - right child index
using TreeNode = std::tuple<KeyDepth, long long, long long>;

class TreeTraverse {
 public:
  explicit TreeTraverse(const std::vector<TreeNode>* tree) : tree_{tree} {}
  void InOrder(const TreeNode& c)
  {
    auto left = std::get<1>(c);
    auto right = std::get<2>(c);

    if (left != -1) {
      InOrder((*tree_)[std::get<1>(c)]);
    }

    order_.push_back(std::get<0>(c));

    if (right != -1) {
      InOrder((*tree_)[std::get<2>(c)]);
    }
  }

  void CleanOrder() { order_.clear(); }
  const std::vector<KeyDepth>& GetOrder() const { return order_; }
 private:
  const std::vector<TreeNode>* tree_;
  std::vector<KeyDepth> order_;
};

#endif  // _COURSES_CHECK_TREE_STRICT_HPP_
