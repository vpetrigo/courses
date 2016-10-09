#include "socket_linux.hpp"
#include <cassert>
#include <cstring>

namespace downloader {

LinuxTCPClientSocket::LinuxTCPClientSocket() : ClientSocket() {}

int LinuxTCPClientSocket::Read(char *input_buf, std::size_t size) {
  Socket_t s = GetSocketFd();
  assert(s != -1);

  int read_bytes = recv(s, input_buf, size, 0);

  if (read_bytes > 0) {
    return read_bytes;
  }

  return -1;
}

bool LinuxTCPClientSocket::Send(const char *output_buf, std::size_t size) {
  // how many bytes have been sent
  std::size_t sent = 0;
  // how many bytes are left to send
  std::size_t left_to_send = size;
  int n = 0;
  Socket_t s = GetSocketFd();
  assert(s != -1);

  while (left_to_send != 0) {
    n = send(s, output_buf + sent, left_to_send, 0);

    if (n == -1) {
      break;
    }

    sent += n;
    left_to_send -= n;
  }

  return (sent == size);
}

bool LinuxTCPClientSocket::Connect(const std::string &host,
                                   const std::string &port) {
  struct addrinfo *res;
  struct addrinfo hints;

  std::memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  int status = getaddrinfo(host.c_str(), port.c_str(), &hints, &res);

  if (status != 0) {
    // error
    return false;
  }

  Socket_t s = -1;
  for (auto it = res; it != nullptr; it = it->ai_next) {
    s = socket(it->ai_family, it->ai_socktype | SOCK_NONBLOCK, it->ai_protocol);

    if (s < 0) {
      return false;
    }

    status = connect(s, it->ai_addr, it->ai_addrlen);
    if (status != -1) {
      SetSocketFd(s);

      break;
    }

    close(s);
    s = -1;
  }

  freeaddrinfo(res);

  return (s != -1);
}

LinuxTCPClientSocket::~LinuxTCPClientSocket() {
  Socket_t s = GetSocketFd();

  if (s != -1) {
    close(GetSocketFd());
  }
}
}