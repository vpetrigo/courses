#include "disjoint_set_rank.hpp"

#include <gtest/gtest.h>

TEST(DisjointSetRank, two_element_set) {
  DisjointSet<std::size_t> ds{2};

  ds.MakeSet(1);
  ds.MakeSet(0);
  ASSERT_EQ(ds.Find(1), 1);
  ASSERT_EQ(ds.Find(0), 0);
  ds.Union(0, 1);
  ASSERT_EQ(ds.Find(0), 1);
}
