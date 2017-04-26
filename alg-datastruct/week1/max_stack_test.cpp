#include "max_stack.hpp"

#include <gtest/gtest.h>

using NumMaxStack = MaxStack<std::size_t>;

TEST(Numeric_MaxStack, multiple_element_stack) {
  constexpr std::size_t SIZE = 10;
  NumMaxStack stack;

  ASSERT_TRUE(stack.Empty());

  for (std::size_t i = 0; i < SIZE; ++i) {
    stack.Push(i);
    ASSERT_EQ(stack.Max(), i);
  }

  for (std::size_t i = SIZE - 1; i > 0; --i) {
    stack.Pop();
    ASSERT_EQ(stack.Max(), i - 1);
  }

  stack.Pop();
  ASSERT_TRUE(stack.Empty());
}
