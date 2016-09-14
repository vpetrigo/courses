#ifndef MAILRU_COURSE_SOCKBUF_HPP
#define MAILRU_COURSE_SOCKBUF_HPP

#include <array>
#include <streambuf>
#include "socket.hpp"

namespace downloader {

template <typename CharT>
class SocketStreamBuf : public std::basic_streambuf<CharT> {
 public:
  using char_type = CharT;
  using Base = std::basic_streambuf<char_type>;
  using traits_type = typename Base::traits_type;
  using int_type = typename traits_type::int_type;
  using off_type = typename traits_type::off_type;

  SocketStreamBuf() {
    // init buffer's put area
    Base::setp(output_buffer_.begin(), output_buffer_.end());
    // init buffer's get area
    Base::setg(input_buffer_.begin(), input_buffer_.begin(),
               input_buffer_.begin());
  }

  ~SocketStreamBuf() = default;

  SocketStreamBuf(const SocketStreamBuf& buf) = delete;
  SocketStreamBuf& operator=(const SocketStreamBuf& buf) = delete;

  void set_socket(int s) { socket_ = s; }

  int get_socket() const { return socket_; }

 protected:
  int_type overflow(int_type ch = traits_type::eof()) {
    if (send_data() && ch != traits_type::eof()) {
      Base::setp(output_buffer_.begin(), output_buffer_.end());
      Base::sputc(ch);
    }

    return ch;
  }

  int_type underflow() {
    if (read_data()) {
      return *Base::gptr();
    }

    return traits_type::eof();
  }

  bool send_data() {
    off_type size = Base::pptr() - Base::pbase();

    if (send(socket_, Base::pbase(), size, 0) == size) {
      return true;
    }

    return false;
  }

  bool read_data() {
    fd_set rdfs;
    constexpr struct timeval tv = {90, 0};
    FD_ZERO(&rdfs);
    FD_SET(socket_, &rdfs);

    int retval = select(socket_ + 1, &rdfs, nullptr, nullptr, &tv);

    if (retval < 0) {
      // select error
    } else if (retval) {
      ssize_t read_bytes =
          recv(socket_, Base::pbase(), input_buffer_.size(), 0);

      if (read_bytes > 0) {
        Base::setg(input_buffer_.begin(), input_buffer_.begin(),
                   input_buffer_.begin() + read_bytes);
        return true;
      }
    }

    return false;
  }

 private:
  static constexpr std::size_t buffer_size = 1024;
  // buffers here
  std::array<char_type, buffer_size> input_buffer_;
  std::array<char_type, buffer_size> output_buffer_;
  int socket_{-1};
};
}

#endif  // MAILRU_COURSE_SOCKBUF_HPP
