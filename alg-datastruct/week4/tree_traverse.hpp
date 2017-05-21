#ifndef _COURSES_TREE_TRAVERSE_HPP_
#define _COURSES_TREE_TRAVERSE_HPP_

#include <tuple>
#include <vector>

// TreeNode for storing in an array or vector
// 0 element - key
// 1 element - left child index
// 2 element - right child index
using TreeNode = std::tuple<long long, long long, long long>;

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

  void PreOrder(const TreeNode& c)
  {
    auto left = std::get<1>(c);
    auto right = std::get<2>(c);

    order_.push_back(std::get<0>(c));

    if (left != -1) {
      PreOrder((*tree_)[std::get<1>(c)]);
    }

    if (right != -1) {
      PreOrder((*tree_)[std::get<2>(c)]);
    }
  }

  void PostOrder(const TreeNode& c)
  {
    auto left = std::get<1>(c);
    auto right = std::get<2>(c);

    if (left != -1) {
      PostOrder((*tree_)[std::get<1>(c)]);
    }

    if (right != -1) {
      PostOrder((*tree_)[std::get<2>(c)]);
    }

    order_.push_back(std::get<0>(c));
  }

  void CleanOrder() { order_.clear(); }
  const std::vector<long long>& GetOrder() const { return order_; }
 private:
  const std::vector<TreeNode>* tree_;
  std::vector<long long> order_;
};

#endif  // _COURSES_TREE_TRAVERSE_HPP_
