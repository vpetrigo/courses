#include "string_hash.hpp"

#include <gtest/gtest.h>

TEST(StringHashSet, add_delete_one_element) {
  HashSet<std::string> ht{1};

  ht.Add("Hello");
  ASSERT_NE(ht.Find("Hello"), ht.End());

  auto check_pair = ht.Check(0);

  ASSERT_EQ(*check_pair.first, "Hello");
  ht.Delete("Hello");
  ASSERT_EQ(ht.Find("Hello"), ht.End());
}

TEST(StringHashSet, add_duplicates) {
  HashSet<std::string> ht{1};

  ht.Add("Hello");
  ht.Add("Hello");
  ht.Add("Hello");
  auto check_pair = ht.Check(0);
  ASSERT_EQ(std::distance(check_pair.first, check_pair.second), 1);
  ht.Add("Test");
  check_pair = ht.Check(0);
  ASSERT_EQ(std::distance(check_pair.first, check_pair.second), 2);
}

TEST(StringHashFunction, hash_test) {
  HashFunction<std::string> hf;

  ASSERT_EQ(hf("world") % 5, hf("Hell0") % 5);
}
