#include "socket.hpp"

namespace downloader {
Socket::Socket() : sock_fd_{INVALID_VALUE}, is_block{true} {}

Socket::Socket(Socket_t sfd, bool is_block)
    : sock_fd_{sfd}, is_block{is_block} {
#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
  if (sock_fd_ == INVALID_SOCKET) {
#else
  if (sock_fd_ < 0) {
#endif
    throw SocketException{};
  }
}

Socket::~Socket() {
#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
  if (sock_fd_ != INVALID_SOCKET) {
    closesocket(sock_fd_);
#else
  if (sock_fd_ > 0) {
    close(sock_fd_);
#endif
  }
}

Socket::Socket(Socket&& s) : sock_fd_{s.sock_fd_}, is_block{s.is_block} {
  s.sock_fd_ = -1;
}

Socket& Socket::operator=(Socket&& s) {
  swap(s);

  return *this;
}

void Socket::swap(Socket& s) noexcept {
  sock_fd_ = std::move(s.sock_fd_);
  is_block = std::move(s.is_block);
  s.sock_fd_ = -1;
}

Socket_t Socket::GetFd() const { return sock_fd_; }
}
