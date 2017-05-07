#include "disjoint_set.hpp"

#include <gtest/gtest.h>

TEST(DB_TableDisjointSet_test, first_test) {
  constexpr std::size_t n_tables{5};
  DB_TableDisjointSet ds{n_tables};

  for (std::size_t i = 0; i < n_tables; ++i) {
    ds.MakeSet(std::make_pair(i, 1));
  }

  // Queries to unite two tables
  ASSERT_EQ(ds.Union(2, 4), 2);
  ASSERT_EQ(ds.Union(1, 3), 2);
  ASSERT_EQ(ds.Union(0, 3), 3);
  ASSERT_EQ(ds.Union(4, 3), 5);
  ASSERT_EQ(ds.Union(4, 2), 5);
}
