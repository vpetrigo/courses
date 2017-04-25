#include "network_queue.h"

#include <gtest/gtest.h>

using NumNetworkQueue = NetworkQueue<int>;

TEST(Numeric_NetworkQueue, one_element_queue) {
  constexpr int TEST_VAL = 5;
  NumNetworkQueue n_queue{1};

  ASSERT_TRUE(n_queue.Empty());
  n_queue.Push(TEST_VAL);
  ASSERT_FALSE(n_queue.Empty());
  ASSERT_TRUE(n_queue.Full());
  ASSERT_EQ(n_queue.Top(), TEST_VAL);

  auto val = n_queue.Pop();

  ASSERT_EQ(val, TEST_VAL);
  ASSERT_FALSE(n_queue.Full());
  ASSERT_TRUE(n_queue.Empty());
}

TEST(Numeric_NetworkQueue, multiple_element_queue) {
  constexpr int QUEUE_SIZE = 5;
  NumNetworkQueue n_queue{QUEUE_SIZE};

  for (std::size_t i = 0; i < QUEUE_SIZE; ++i) {
    n_queue.Push(static_cast<int>(i));
  }

  ASSERT_TRUE(n_queue.Full());

  for (std::size_t i = 0; i < QUEUE_SIZE; ++i) {
    ASSERT_EQ(n_queue.Pop(), i);
  }

  ASSERT_TRUE(n_queue.Empty());
}

TEST(Numeric_NetworkQueue, multiple_element_queue_overflow) {
  constexpr int QUEUE_SIZE = 5;
  NumNetworkQueue n_queue{QUEUE_SIZE};

  for (std::size_t i = 0; i < QUEUE_SIZE; ++i) {
    n_queue.Push(static_cast<int> (i));
  }

  for (std::size_t i = 0; i < QUEUE_SIZE/2; ++i) {
    ASSERT_EQ(n_queue.Pop(), i);
  }

  ASSERT_FALSE(n_queue.Full());
  ASSERT_EQ(n_queue.Size(), QUEUE_SIZE - (QUEUE_SIZE / 2));

  for (std::size_t i = QUEUE_SIZE; i < (QUEUE_SIZE + QUEUE_SIZE / 2); ++i) {
    n_queue.Push(static_cast<int>(i));
  }

  ASSERT_TRUE(n_queue.Full());
  ASSERT_EQ(n_queue.Size(), QUEUE_SIZE);

  for (std::size_t i = QUEUE_SIZE/2; i < (QUEUE_SIZE + QUEUE_SIZE / 2); ++i) {
    ASSERT_EQ(n_queue.Pop(), i);
  }

  ASSERT_TRUE(n_queue.Empty());
  ASSERT_EQ(n_queue.Size(), 0);
}

TEST(Numeric_NetworkQueue, zero_size_queue) {
  NumNetworkQueue n_queue{0};

  ASSERT_TRUE(n_queue.Full());
  ASSERT_EQ(n_queue.Size(), 0);
  ASSERT_TRUE(n_queue.Empty());
}
