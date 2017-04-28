#ifndef _BUILD_HEAP_HPP_
#define _BUILD_HEAP_HPP_

#include <iterator>
#include <vector>
#include <utility>

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
  std::size_t length = static_cast<std::size_t>(std::distance(first, last));

  for (std::size_t i = static_cast<std::size_t>(length / 2); i <= length / 2; --i) {
    SiftDown(first, last, length, compare, i);
  }
}

template <typename T, typename Compare = std::less<T>>
class HeapBuilder {
 public:
  explicit HeapBuilder(const Compare& compare = Compare{}) : compare_{compare} {}

  virtual ~HeapBuilder() = default;

  HeapBuilder(const HeapBuilder& hb) = default;
  HeapBuilder& operator=(const HeapBuilder& hb) = default;

  HeapBuilder(HeapBuilder&& hb) noexcept = default;
  HeapBuilder& operator=(HeapBuilder&& hb) noexcept = default;

  template <typename It>
  void BuildHeap(It first, It last) {
    std::size_t length = static_cast<std::size_t>(std::distance(first, last));
    rearrange_.clear();

    for (std::size_t i = length / 2; i <= length / 2; --i) {
      SiftDown(first, last, length, i);
    }
  }

  const std::vector<std::pair<std::size_t, std::size_t>>& Rearrange() const {
    return rearrange_;
  };
 protected:
  template <typename It>
  void SiftDown(It first, It last, const std::size_t length, std::size_t index) {
    auto smallest_index = index;
    bool finish = false;

    while (!finish) {
      auto left_child = 2 * index + 1;
      auto right_child = 2 * index + 2;

      if (left_child < length && compare_(*(first + left_child), *(first + smallest_index))) {
        smallest_index = left_child;
      }

      if (right_child < length && compare_(*(first + right_child), *(first + smallest_index))) {
        smallest_index = right_child;
      }

      if (smallest_index != index) {
        std::iter_swap(first + smallest_index, first + index);
        rearrange_.emplace_back(std::make_pair(index, smallest_index));
        index = smallest_index;
      }
      else {
        finish = true;
      }
    }
  }
 private:
  Compare compare_;
  std::vector<std::pair<std::size_t, std::size_t>> rearrange_;
};

#endif  // _BUILD_HEAP_HPP_
