#include "tree_height.hpp"

#include <gtest/gtest.h>

TEST(Tree_height, five_element_tree) {
  std::vector<int> tree_list{4, -1, 4, 1, 1};

  ASSERT_EQ(TreeHeight(tree_list), 3);
}

TEST(Tree_height, four_element_tree_2) {
  std::vector<int> tree_list{-1, 0, 4, 0, 3};

  ASSERT_EQ(TreeHeight(tree_list), 4);
}

TEST(Tree_height, ten_element_tree) {
  std::vector<int> tree_list{9, 7, 5, 5, 2, 9, 9, 9, 2, -1};

  ASSERT_EQ(TreeHeight(tree_list), 4);
}
