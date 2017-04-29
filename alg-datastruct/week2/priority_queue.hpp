#ifndef _PRIORITY_QUEUE_HPP_
#define _PRIORITY_QUEUE_HPP_

#include <functional>
#include <vector>

template <typename T, typename Compare = std::less<T>>
class PriorityQueue {
 public:
  explicit PriorityQueue(const Compare& compare = Compare{})
      : compare_{compare}, heap_{}
  {
  }

  void AddElement(T&& element)
  {
    heap_.emplace_back(std::move(element));
    SiftUp(heap_.size() - 1);
  }

  void AddElement(const T& element)
  {
    heap_.push_back(element);
    SiftUp(heap_.size() - 1);
  }

  T ExtractTop()
  {
    T top{heap_.front()};

    std::swap(heap_.front(), heap_.back());
    heap_.pop_back();
    SiftDown(0);

    return top;
  }

  std::size_t Size() const { return heap_.size(); }
 protected:
  std::size_t Parent(std::size_t index) { return (index - 1) / 2; }
  std::size_t LeftChild(std::size_t index) { return 2 * index + 1; }
  std::size_t RightChild(std::size_t index) { return 2 * index + 2; }
  void SiftUp(std::size_t index)
  {
    while (index > 0 && compare_(heap_[Parent(index)], heap_[index])) {
      std::swap(heap_[Parent(index)], heap_[index]);
      index = Parent(index);
    }
  }

  void SiftDown(std::size_t index)
  {
    bool finish = false;
    std::size_t smallest_index = index;

    while (!finish) {
      auto l_child = LeftChild(index);
      auto r_child = RightChild(index);

      if (l_child < heap_.size() &&
          compare_(heap_[smallest_index], heap_[l_child])) {
        smallest_index = l_child;
      }

      if (r_child < heap_.size() &&
          compare_(heap_[smallest_index], heap_[r_child])) {
        smallest_index = r_child;
      }

      if (smallest_index != index) {
        std::swap(heap_[smallest_index], heap_[index]);
        index = smallest_index;
      }
      else {
        finish = true;
      }
    }
  }

 private:
  Compare compare_;
  std::vector<T> heap_;
};

#endif  // _PRIORITY_QUEUE_HPP_
