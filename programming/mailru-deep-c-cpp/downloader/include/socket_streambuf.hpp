#ifndef MAILRU_SOCKET_STREAMBUF_HPP
#define MAILRU_SOCKET_STREAMBUF_HPP

#include <cstddef>
#include <cstring>
#include <iterator>
#include <limits>
#include <streambuf>
#include <vector>

namespace downloader {
template <typename Allocator>
class SockStreambuf : public std::streambuf {
 public:
  using pointer = char_type*;
  using const_pointer = const char_type*;

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

  std::pair<const_pointer, const_pointer> data() const {
    return std::make_pair(gptr(), pptr() - gptr());
  };

  std::pair<pointer, pointer> prepare(std::size_t n) {
    reserve(n);
    return std::make_pair(pptr(), pptr() + n);
  };
  // Appends characters from the output sequence to the input
  void commit(std::size_t n) {
    if (pptr() + n > epptr()) {
      n = epptr() - pptr();
    }
    pbump(static_cast<int>(n));
    setg(eback(), gptr(), pptr());
  }
  // Remove characters from the input sequence.
  void consume(std::size_t n) {
    if (egptr() < pptr()) {
      setg(&buffer_.front(), gptr(), pptr());
    }
    if (gptr() + n > pptr()) {
      n = pptr() - gptr();
    }
    gbump(static_cast<int>(n));
  }

 protected:
  static constexpr std::size_t default_buffer_size = 128;
  static constexpr std::size_t min_buffer_size = 1;

  int_type overflow(int_type ch) override {
    if (!traits_type::eq_int_type(ch, traits_type::eof())) {
      if (pptr() == epptr()) {
        std::size_t buffer_size = pptr() - gptr();

        if (buffer_size < max_size_) {
          buffer_.reserve(
              std::min(default_buffer_size, max_size_ - buffer_size));
        }
      }

      *pptr() = traits_type::to_char_type(ch);
      pbump(1);

      return ch;
    }

    return traits_type::eof();
  }

  int_type underflow()
  {
    if (gptr() < pptr()) {
      setg(&buffer_.front(), gptr(), pptr());
      return traits_type::to_int_type(*gptr());
    }

    return traits_type::eof();
  }

  void reserve(std::size_t n) {
    std::size_t gnext = gptr() - &buffer_.front();
    std::size_t pnext = pptr() - &buffer_.front();
    std::size_t pend = epptr() - &buffer_.front();

    if (n <= pend - pnext) {
      // already has enought space
      return;
    }

    if (gnext > 0) {
      // move content from get area to the beginning of the buffer
      pnext -= gnext;
      std::memmove(&buffer_.front(), std::next(&buffer_.front(), gnext), pnext);
    }

    if (n > pend - pnext) {
      if (n <= max_size_ && pnext <= max_size_ - n) {
        pend = pnext + n;
        buffer_.resize(std::max(pend, min_buffer_size));
      }
      else {
        throw std::runtime_error{"Cannot increase the streambuf size"};
      }
    }

    setg(&buffer_.front(), &buffer_.front(),
         std::next(&buffer_.front(), pnext));
    setp(std::next(&buffer_.front(), pnext),
         std::next(&buffer_.front(), pnext));
  }

 private:
  std::size_t max_size_;
  std::vector<char_type, Allocator> buffer_;
};
}  // namespace downloader

#endif  // MAILRU_SOCKET_STREAMBUF_HPP
