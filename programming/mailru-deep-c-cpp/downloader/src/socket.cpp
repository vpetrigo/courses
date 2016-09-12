#include "socket.hpp"
#include <system_error>

namespace downloader {

Socket::Socket(int sock_family, int sock_type, int protocol)
    : sock_fd_(socket(sock_family, sock_type, protocol)) {
  if (sock_fd_ == -1) {
    // cannot create socket
    throw std::system_error{};
  }
}

}  // namespace downloader
