#include "priority_queue.hpp"

#include <algorithm>
#include <random>
#include <gtest/gtest.h>

TEST(Priority_Queue, small_heap_sort) {
  constexpr std::size_t SIZE = 3;
  PriorityQueue<std::size_t, std::greater<std::size_t>> queue;
  std::array<std::size_t, SIZE> arr;

  for (std::size_t i = SIZE - 1; i <= SIZE; --i) {
    queue.AddElement(i);
  }

  for (std::size_t i = 0; i < SIZE; ++i) {
    arr[i] = queue.ExtractTop();
  }

  ASSERT_TRUE(std::is_sorted(arr.cbegin(), arr.cend()));
}

TEST(Priority_Queue, big_random_array_sort) {
  constexpr std::size_t SIZE = 1024;
  std::array<std::size_t, SIZE> arr;
  PriorityQueue<std::size_t, std::greater<std::size_t>> queue;
  std::random_device rd{};
  std::mt19937 gen(rd());
  std::binomial_distribution<std::size_t> dist{4096, 0.4};

  for (std::size_t i = 0; i < SIZE; ++i) {
    queue.AddElement(dist(gen));
  }

  for (auto& elem : arr) {
    elem = queue.ExtractTop();
  }

  ASSERT_TRUE(std::is_sorted(arr.cbegin(), arr.cend()));
}

TEST(Priority_Queue, size_test) {
  PriorityQueue<std::size_t> queue;

  queue.AddElement(1);
  ASSERT_EQ(queue.Size(), 1);
  queue.AddElement(2);
  ASSERT_EQ(queue.Size(), 2);
  queue.AddElement(3);
  ASSERT_EQ(queue.Size(), 3);
  queue.ExtractTop();
  ASSERT_EQ(queue.Size(), 2);
  queue.ExtractTop();
  ASSERT_EQ(queue.Size(), 1);
  queue.ExtractTop();
  ASSERT_EQ(queue.Size(), 0);
}
