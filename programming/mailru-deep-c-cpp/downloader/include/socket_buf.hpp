#ifndef MAILRU_COURSE_SOCKBUF_HPP
#define MAILRU_COURSE_SOCKBUF_HPP

#include <streambuf>
#include <iterator>
#include <array>

namespace downloader {

template <typename CharT>
class SocketStreamBuf : public std::basic_streambuf<CharT> {
public:

  using char_type = CharT;
  using traits_type = typename std::basic_streambuf<char_type>::traits_type;

  SocketStreamBuf() {
    // init buffer's put area
    setp(std::begin(output_buffer_), std::end(output_buffer_));
    // init buffer's get area
    setg(std::begin(input_buffer_), std::end(input_buffer_));
  }

  ~SocketStreamBuf() = default;

  SocketStreamBuf(const SocketStreamBuf& buf) = delete;
  SocketStreamBuf& operator=(const SocketStreamBuf& buf) = delete;

  void set_socket(int s) {
    socket_ = s;
  }

  int get_socket() const {
    return socket_;
  }
private:
  static constexpr std::size_t buffer_size = 1024;
  // buffers here
  std::array<char_type, buffer_size> input_buffer_;
  std::array<char_type, buffer_size> output_buffer_;
  int socket_{-1};
};

}

#endif // MAILRU_COURSE_SOCKBUF_HPP
