#ifndef _MAX_STACK_HPP_
#define _MAX_STACK_HPP_

#include <stack>

template <typename T>
class MaxStack {
 public:
  MaxStack() : elem_stack_{}, max_stack_{} {}

  void Push(const T& el)
  {
    elem_stack_.push(el);

    if (!max_stack_.empty()) {
      max_stack_.push((el > max_stack_.top()) ? el : max_stack_.top());
    }
    else {
      max_stack_.push(el);
    }
  }

  void Push(T&& el)
  {
    elem_stack_.emplace(std::forward<T>(el));

    if (!max_stack_.empty()) {
      max_stack_.push((elem_stack_.top() > max_stack_.top())
                          ? elem_stack_.top()
                          : max_stack_.top());
    }
    else {
      max_stack_.push(elem_stack_.top());
    }
  }

  void Pop() {
    elem_stack_.pop();
    max_stack_.pop();
  }

  const T& Max() const { return max_stack_.top(); }

  T& Max() { return max_stack_.top(); }

  bool Empty() const {
    return elem_stack_.empty();
  }

  std::size_t Size() const {
    return elem_stack_.size();
  }
 private:
  std::stack<T> elem_stack_;
  std::stack<T> max_stack_;
};

#endif  // _MAX_STACK_HPP_
