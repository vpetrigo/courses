#include "max_stack.hpp"

#include <iostream>
#include <vector>

using NumMaxStack = MaxStack<std::size_t>;

int main()
{
  std::size_t elements_q;
  std::size_t max_window_size;
  NumMaxStack input;
  NumMaxStack output;

  std::cin >> elements_q;

  std::vector<size_t> elements(elements_q);

  for (auto& elem : elements) {
    std::cin >> elem;
  }

  std::cin >> max_window_size;

  for (const auto& elem : elements) {
    input.Push(elem);

    if (input.Size() == max_window_size) {
      // input stack is overflowed, move all elements to the
      // output stack
      while (!input.Empty()) {
        output.Push(input.Top());
        input.Pop();
      }
    }

    if (!output.Empty()) {
      // maximum either in output or input stack ;)
      auto& max_in_frame =
          (input.Empty()) ? output.Max() : std::max(input.Max(), output.Max());

      std::cout << max_in_frame << ' ';
      output.Pop();
    }
  }

  return 0;
}
