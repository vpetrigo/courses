#ifndef _BRACKETS_HPP_
#define _BRACKETS_HPP_

#include <initializer_list>
#include <vector>

template <typename T>
class Stack {
 public:
  Stack() : stack_{} {}
  Stack(std::initializer_list<T>& l) : stack_{l} {}
  Stack(const Stack& s) = default;
  Stack& operator=(const Stack& s) = default;

  Stack(Stack&& s) noexcept = default;
  Stack& operator=(Stack&& s) noexcept = default;

  ~Stack() = default;

  void Push(T&& el) { stack_.emplace_back(el); }
  void Push(const T& el) { stack_.emplace_back(el); }
  T Pop()
  {
    T back{stack_.back()};

    stack_.pop_back();

    return back;
  }

  bool Empty() { return stack_.empty(); }
 private:
  std::vector<T> stack_;
};

#endif  // _BRACKETS_HPP_
