#include "build_heap.hpp"

#include <array>
#include <algorithm>
#include <functional>
#include <gtest/gtest.h>

TEST(Build_Heap, array_sort) {
  std::array<int, 3> arr{3, 2, 1};

  ASSERT_FALSE(std::is_heap(arr.cbegin(), arr.cend(), std::greater<int>{}));
  BuildHeap(arr.begin(), arr.end());
  ASSERT_TRUE(std::is_heap(arr.cbegin(), arr.cend(), std::greater<int>{}));
}

TEST(Build_Heap, big_array_sort) {
  std::array<std::size_t, 128> arr;

  for (std::size_t i = 0; i < arr.size(); ++i) {
    arr[arr.size() - i - 1] = i;
  }

  ASSERT_FALSE(std::is_heap(arr.cbegin(), arr.cend(), std::greater<size_t>{}));
  BuildHeap(arr.begin(), arr.end());
  ASSERT_TRUE(std::is_heap(arr.cbegin(), arr.cend(), std::greater<std::size_t>{}));
}
