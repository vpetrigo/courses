#include "brackets.hpp"

#include <array>
#include <gtest/gtest.h>

using char_stack = Stack<char>;

TEST(Stack_test, Push_one_element) {
  char_stack ns;
  constexpr char val = '[';

  ASSERT_TRUE(ns.Empty());
  ns.Push(val);
  ASSERT_FALSE(ns.Empty());
  ASSERT_EQ(ns.Pop(), val);
}

TEST(Stack_test, Push_multiple_elements) {
  std::array<char, 2> val{'[', ']'};
  char_stack ch_stack;

  for (const auto& e : val) {
    ch_stack.Push(e);
  }

  ASSERT_FALSE(ch_stack.Empty());

  for (auto it = val.crbegin(); it != val.crend(); ++it) {
    ASSERT_EQ(ch_stack.Pop(), *it);
  }

  ASSERT_TRUE(ch_stack.Empty());
}

TEST(Stack_test, Push_pop_sequence) {
  std::array<char, 4> val{'a', 'b', 'c', 'd'};
  char_stack ch_stack;
  auto it = val.cbegin();

  ASSERT_TRUE(ch_stack.Empty());
  ch_stack.Push(*it++);
  ch_stack.Push(*it);
  ASSERT_EQ(ch_stack.Pop(), *it++);
  ch_stack.Push(*it++);
  ch_stack.Push(*it);

  for (const auto& e : {'d', 'c', 'a'}) {
    ASSERT_EQ(ch_stack.Pop(), e);
  }

  ASSERT_TRUE(ch_stack.Empty());
}
