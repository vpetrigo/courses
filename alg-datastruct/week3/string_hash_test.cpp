#include "string_hash.hpp"

#include <gtest/gtest.h>

TEST(StringHashSet, add_delete_one_element) {
  HashTable<std::string> ht{1};

  ht.Add("Hello");
  ASSERT_NE(ht.Find("Hello"), ht.End());

  auto check_pair = ht.Check(0);

  ASSERT_EQ(*check_pair.first, "Hello");
  ht.Delete("Hello");
  ASSERT_EQ(ht.Find("Hello"), ht.End());
}

TEST(StringHashFunction, hash_test) {
  HashFunction<std::string> hf;

  ASSERT_EQ(hf("world") % 5, hf("Hell0") % 5);
}
