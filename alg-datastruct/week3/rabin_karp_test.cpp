#include "rabin_karp.hpp"

#include <gtest/gtest.h>

TEST(RabinKarp_Hash, find_occurence1) {
  RabinKarp rk{"Hello"};
  std::string text{"Hello Hello Hello"};
  const std::vector<std::size_t> occ{0, 6, 12};

  const auto occurence = rk.GetPatternOccurence(text);

  ASSERT_EQ(occurence.size(), occ.size());
  const auto mismatch_pos = std::mismatch(occurence.cbegin(), occurence.cend(), occ.cbegin());
  ASSERT_EQ(mismatch_pos.first, occurence.cend());
  ASSERT_EQ(mismatch_pos.second, occ.cend());
}

TEST(RabinKarp_Hash, find_occurence2) {
  RabinKarp rk{"aba"};
  std::string text{"abacaba"};
  const std::vector<std::size_t> occ{0, 4};

  const auto occurence = rk.GetPatternOccurence(text);

  ASSERT_EQ(occurence.size(), occ.size());
  const auto mismatch_pos = std::mismatch(occurence.cbegin(), occurence.cend(), occ.cbegin());
  ASSERT_EQ(mismatch_pos.first, occurence.cend());
  ASSERT_EQ(mismatch_pos.second, occ.cend());
}

TEST(RabinKarp_Hash, find_occurence3) {
  RabinKarp rk{"aaaaa"};
  std::string text{"baaaaaaa"};
  const std::vector<std::size_t> occ{1, 2, 3};

  const auto occurence = rk.GetPatternOccurence(text);

  ASSERT_EQ(occurence.size(), occ.size());
  const auto mismatch_pos = std::mismatch(occurence.cbegin(), occurence.cend(), occ.cbegin());
  ASSERT_EQ(mismatch_pos.first, occurence.cend());
  ASSERT_EQ(mismatch_pos.second, occ.cend());
}

TEST(RabinKarp_Hash, find_occurence4) {
  RabinKarp rk{"Test"};
  std::string text{"testTesttesT"};
  const std::vector<std::size_t> occ{4};

  const auto occurence = rk.GetPatternOccurence(text);

  ASSERT_EQ(occurence.size(), occ.size());
  const auto mismatch_pos = std::mismatch(occurence.cbegin(), occurence.cend(), occ.cbegin());
  ASSERT_EQ(mismatch_pos.first, occurence.cend());
  ASSERT_EQ(mismatch_pos.second, occ.cend());
}
