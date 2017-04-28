#ifndef _BUILD_HEAP_HPP_
#define _BUILD_HEAP_HPP_

#include <iterator>
#include <iostream>

template <typename It, typename Cmp>
void SiftDown(It first, It last, const std::size_t length, const Cmp& compare,
              std::size_t index)
{
  auto smallest_elem = index;
  bool finish = false;

  while (!finish) {
    auto left_child = 2 * index + 1;
    auto right_child = 2 * index + 2;

    if (left_child < length &&
        compare(*(first + left_child), *(first + smallest_elem))) {
      smallest_elem = left_child;
    }

    if (right_child < length &&
        compare(*(first + right_child), *(first + smallest_elem))) {
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

template <typename It, typename Cmp = std::less<typename std::iterator_traits<It>::value_type>>
void BuildHeap(It first, It last, const Cmp& compare = Cmp{})
{
  auto length = std::distance(first, last);

  for (std::size_t i = static_cast<size_t>(length / 2); i <= length / 2; --i) {
    SiftDown(first, last, length, compare, i);
  }
}

#endif  // _BUILD_HEAP_HPP_
