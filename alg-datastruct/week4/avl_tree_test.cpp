#include "avl_tree.hpp"

#include <iostream>
#include <gtest/gtest.h>

TEST(AVL_TreeTest, add_one_element) {
  AVL_Tree<std::size_t> tree;

  tree.Insert(5);
  ASSERT_EQ(*tree.Find(5), 5);
}

TEST(AVL_TreeTest, add_multiple_elements) {
  AVL_Tree<std::size_t> tree;
  constexpr std::size_t n_elems{100000};

  for (std::size_t i = 0; i < n_elems; ++i) {
    tree.Insert(i);
  }

  for (std::size_t i = 0; i < n_elems; ++i) {
    ASSERT_EQ(*tree.Find(i), i);
  }
}
