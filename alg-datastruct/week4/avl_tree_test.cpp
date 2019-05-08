#include "avl_tree.hpp"

#include <gtest/gtest.h>

TEST(AVL_TreeTest, add_one_element)
{
    AVL_Tree<std::size_t> tree;

    tree.Insert(5);
    ASSERT_EQ(*tree.Find(5), 5);
}

TEST(AVL_TreeTest, add_multiple_elements)
{
    AVL_Tree<std::size_t> tree;
    constexpr std::size_t n_elems{1000000};

    for (std::size_t i = 0; i < n_elems; ++i) {
        tree.Insert(i);
    }

    for (std::size_t i = 0; i < n_elems; ++i) {
        ASSERT_EQ(*tree.Find(i), i);
    }
}

TEST(AVL_TreeTest, remove_multiple_elements)
{
    AVL_Tree<std::size_t> tree;
    constexpr std::size_t n_elems{1000000};

    for (std::size_t i = 0; i < n_elems; ++i) {
        tree.Insert(i);
    }

    tree.Remove(0);
    tree.Remove(n_elems / 2);
    tree.Remove(n_elems - 1);

    for (std::size_t i = 0; i < n_elems; ++i) {
        if (i == 0 || i == n_elems / 2 || i == n_elems - 1) {
            ASSERT_EQ(tree.Find(i), nullptr);
        }
        else {
            ASSERT_EQ(*tree.Find(i), i);
        }
    }
}

TEST(AVL_TreeTest, subtree_size)
{
    AVL_Tree<std::size_t> tree;
    constexpr std::size_t n_elems{100};

    for (std::size_t i = 0; i < n_elems; ++i) {
        tree.Insert(i);
    }

    ASSERT_EQ(tree.GetRootSubtreeSize(), n_elems);
}

TEST(AVL_TreeTest, subtree_size_with_remove)
{
    AVL_Tree<std::size_t> tree;
    constexpr std::size_t n_elems{100};

    for (std::size_t i = 0; i < n_elems; ++i) {
        tree.Insert(i);
    }

    ASSERT_EQ(tree.GetRootSubtreeSize(), n_elems);

    for (std::size_t i = 0; i < n_elems / 2; ++i) {
        tree.Remove(i);
    }

    ASSERT_EQ(tree.GetRootSubtreeSize(), n_elems / 2);

    for (std::size_t i = 0; i < n_elems / 2; ++i) {
        tree.Insert(i + n_elems);
    }

    ASSERT_EQ(tree.GetRootSubtreeSize(), n_elems);
}
