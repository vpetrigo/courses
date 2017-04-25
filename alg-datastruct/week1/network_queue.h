#ifndef _NETWORK_QUEUE_H_
#define _NETWORK_QUEUE_H_

#include <memory>

template<typename T>
class NetworkQueue {
 public:
  explicit NetworkQueue(const std::size_t queue_size) : queue_{std::make_unique<T[]>(queue_size)},
                                                        queue_indexes_{0, 0},
                                                        queue_size_{0},
                                                        queue_capacity_{queue_size} {}

  ~NetworkQueue() = default;

  NetworkQueue(const NetworkQueue &nq) = delete;
  NetworkQueue& operator=(const NetworkQueue &nq) = delete;

  NetworkQueue(NetworkQueue &&nq) noexcept = default;
  NetworkQueue& operator=(NetworkQueue &&nq) noexcept = default;

  bool Empty() const {
    return (queue_size_ == 0);
  }

  bool Full() const {
    return (queue_size_ == queue_capacity_);
  }

  std::size_t Size() const {
    return queue_size_;
  }

  void Push(const T &el) {
    queue_[queue_indexes_.second] = el;
    queue_indexes_.second = (queue_indexes_.second + 1)%queue_capacity_;
    ++queue_size_;
  }

  void Push(T&& el) {
    queue_[queue_indexes_.second] = std::move(el);
    queue_indexes_.second = (queue_indexes_.second + 1)%queue_capacity_;
    ++queue_size_;
  }

  const T& Top() const {
    return queue_[queue_indexes_.first];
  }

  T& Top() {
    return queue_[queue_indexes_.first];
  };

  T Pop() {
    T ret{queue_[queue_indexes_.first]};

    queue_indexes_.first = (queue_indexes_.first + 1)%queue_capacity_;
    --queue_size_;

    return ret;
  }
 private:
  std::unique_ptr<T[]> queue_;
  std::pair<std::size_t, std::size_t> queue_indexes_;
  std::size_t queue_size_;
  std::size_t queue_capacity_;
};

#endif // _NETWORK_QUEUE_H_
