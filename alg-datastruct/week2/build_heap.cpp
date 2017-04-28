#include "build_heap.hpp"

#include <vector>

int main() {
  std::size_t input_size;

  std::cin >> input_size;

  std::vector<std::size_t> numbers(input_size);

  for (auto& elem : numbers) {
    std::cin >> elem;
  }

  BuildHeap(numbers.begin(), numbers.end());

  return 0;
}
