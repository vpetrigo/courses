#include "check_tree_strict.hpp"

#include <algorithm>
#include <gtest/gtest.h>

TEST(TreeStrict, correct_tree) {
  std::vector<TreeNode> tree{{{2, 0}, 1, 2}, {{1, 1}, -1, -1}, {{2, 1}, -1, -1}};
  TreeTraverse traverse{&tree};

  traverse.InOrder(tree.front());
  ASSERT_TRUE(std::is_sorted(traverse.GetOrder().cbegin(), traverse.GetOrder().cend()));
}

TEST(TreeStrict, incorrect_tree) {
  std::vector<TreeNode> tree{{{2, 0}, 1, 2}, {{1, 1}, -1, 2}, {{2, 2}, -1, -1}};
  TreeTraverse traverse{&tree};

  traverse.InOrder(tree.front());
  ASSERT_FALSE(std::is_sorted(traverse.GetOrder().cbegin(), traverse.GetOrder().cend()));
}
