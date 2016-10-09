#include "socket.hpp"

namespace downloader {
Socket_t ClientSocket::GetSocketFd() const {
  return sock_fd_;
}

void ClientSocket::SetSocketFd(Socket_t s) {
  sock_fd_ = s;
}
}
