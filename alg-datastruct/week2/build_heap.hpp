#ifndef _BUILD_HEAP_HPP_
#define _BUILD_HEAP_HPP_

#include <iterator>

template <typename It>
void SiftDown(It first, It last, const std::size_t length, std::size_t index)
{
  auto left_child = 2 * index + 1;
  auto right_child = 2 * index + 2;
  auto smallest_elem = index;
  bool finish = false;

  while (!finish) {
    left_child = 2 * index + 1;
    right_child = 2 * index + 2;

    if (left_child < length &&
        *(first + left_child) < *(first + smallest_elem)) {
      smallest_elem = left_child;
    }

    if (right_child < length &&
        *(first + right_child) < *(first + smallest_elem)) {
      smallest_elem = right_child;
    }

    if (smallest_elem != index) {
      std::iter_swap(first + index, first + smallest_elem);
      index = smallest_elem;
    }
    else {
      finish = true;
    }
  }
}

template <typename It>
void BuildHeap(It first, It last)
{
  auto length = std::distance(first, last);

  for (std::size_t i = length / 2; i <= length / 2; --i) {
    SiftDown(first, last, length, i);
  }
}

#endif  // _BUILD_HEAP_HPP_
