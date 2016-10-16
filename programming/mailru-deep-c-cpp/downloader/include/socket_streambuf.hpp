#ifndef MAILRU_SOCKET_STREAMBUF_HPP
#define MAILRU_SOCKET_STREAMBUF_HPP

#include <cstddef>
#include <limits>
#include <streambuf>
#include <vector>
#include <iterator>

namespace downloader {
template <typename Allocator>
class SockStreambuf : public std::streambuf {
 public:
  SockStreambuf(
      std::size_t maximum_size = std::numeric_limits<std::size_t>::max(),
      const Allocator& alloc = Allocator{})
      : max_size_{maximum_size}, buffer_{alloc} {
    std::size_t put_end = std::min(max_size_, default_buffer_size);
    buffer_.resize(std::max(put_end, min_buffer_size));
    setp(&buffer_.front(), std::next(&buffer_.front(), put_end));
    setg(&buffer_.front(), &buffer_.front(), &buffer_.front());
  }

  SockStreambuf(const SockStreambuf&) = delete;
  SockStreambuf& operator=(const SockStreambuf&) = delete;

  std::size_t size() const { return gptr() - pptr(); }

  std::size_t max_size() const { return max_size_; }

 protected:
  static constexpr std::size_t default_buffer_size = 128;
  static constexpr std::size_t min_buffer_size = 1;

 private:
  std::size_t max_size_;
  std::vector<char_type, Allocator> buffer_;
};
}  // namespace downloader

#endif  // MAILRU_SOCKET_STREAMBUF_HPP
