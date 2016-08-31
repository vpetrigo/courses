#include <gtest/gtest.h>
#include "disjoint_set.hpp"

TEST(DisjointSet, simple_test) {
  constexpr std::size_t size = 2;
  DisjointSet s{size};

  for (std::size_t i = 0; i < size; ++i) {
    ASSERT_EQ(s.Find(i), i);
  }
}

TEST(DisjointSet, unite_test_pair) {
  constexpr std::size_t size = 6;
  DisjointSet s{size};

  for (std::size_t i = 0; i < size; i += 2) {
    s.Unite(i, i + 1);
    ASSERT_EQ(s.Find(i), s.Find(i + 1));
  }
}

TEST(DisjointSet, unite_test_full) {
  constexpr std::size_t size = 6;
  DisjointSet s{size};

  for (std::size_t i = 0; i < size; ++i) {
    s.Unite(i, i + 1);

    if (i != 0) {
      ASSERT_EQ(s.Find(0), s.Find(i));
    }
  }
}
