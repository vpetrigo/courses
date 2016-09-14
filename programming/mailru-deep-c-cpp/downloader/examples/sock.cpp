#include "socket_buf.hpp"
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>

using CSocketStreamBuf = donwloader::SocketStreamBuf<char>;

int main() {
  struct addrinfo *result = nullptr;
  int sock_fd;
  std::iostream ios;

  if (getaddrinfo("www.google.com", "80", nullptr, &result) != 0) {
    return 1;
  }

  if (result != nullptr) {
    std::cout << "found" << std::endl;
    sock_fd = socket(result->ai_family, result->ai_socktype | SOCK_NONBLOCK, result->ai_protocol);

    if (sock_fd == -1) {
      std::cout << "Socket creation error" << std::endl;
      return 2;
    }

    if (!connect(sock_fd, result->ai_addr, result->ai_addrlen)) {
      std::cout << "Connection error" << std::endl;
      return 3;
    }
  }

  CSocketStreamBuf css;
  css.set_socket(sock_fd);
  std::iostream ios{css};

  ios << "CONNECT www.google.com" << std::endl << std::endl;
  std::cout << ios;

  freeaddrinfo(result);
  close(sock_fd);

  return 0;
}
