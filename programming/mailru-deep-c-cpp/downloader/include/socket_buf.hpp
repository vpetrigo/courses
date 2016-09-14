#ifndef MAILRU_COURSE_SOCKBUF_HPP
#define MAILRU_COURSE_SOCKBUF_HPP

#include <array>
#include <iostream>
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

  ~SocketStreamBuf() { sync(); }

  SocketStreamBuf(const SocketStreamBuf& buf) = delete;
  SocketStreamBuf& operator=(const SocketStreamBuf& buf) = delete;

  void set_socket(int s) { socket_ = s; }

  int get_socket() const { return socket_; }

 protected:
  int_type overflow(int_type ch = traits_type::eof()) override {
    if (send_data() && ch != traits_type::eof()) {
      Base::setp(output_buffer_.begin(), output_buffer_.end());
      Base::sputc(ch);
    }

    return ch;
  }

  int_type underflow() override {
    // if we have something to send - send it
    // otherwise we might not send something we want to
    // get response to
    sync();
    if (read_data()) {
      // here we may have a value = 255 that would be interpret
      // as EOF in term of default signed char
      return static_cast<unsigned char>(*Base::gptr());
    }

    return traits_type::eof();
  }

  int sync() override {
    constexpr int SUCCESS = 0;

    if (send_data()) {
      return SUCCESS;
    }

    return traits_type::eof();
  }

  bool send_data() {
    off_type size = Base::pptr() - Base::pbase();

    if (size == 0 || send(socket_, Base::pbase(), size, 0) == size) {
      Base::pbump(-size);
      return true;
    }

    return false;
  }

  bool read_data() {
    fd_set read;
    struct timeval tv = {90, 0};
    FD_ZERO(&read);
    FD_SET(socket_, &read);

    int retval = select(socket_ + 1, &read, nullptr, nullptr, &tv);

    if (retval > 0) {
      ssize_t read_bytes =
          recv(socket_, input_buffer_.begin(), input_buffer_.size(), 0);

      if (read_bytes > 0) {
        Base::setg(input_buffer_.begin(), input_buffer_.begin(),
                   input_buffer_.begin() + read_bytes);
        return true;
      }
    }

    return false;
  }

 private:
  static constexpr std::size_t buffer_size = 1;
  // buffers here
  std::array<char_type, buffer_size> input_buffer_;
  std::array<char_type, buffer_size> output_buffer_;
  int socket_{-1};
};
}

#endif  // MAILRU_COURSE_SOCKBUF_HPP
