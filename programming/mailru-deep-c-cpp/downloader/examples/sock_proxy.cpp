#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include "socket_buf.hpp"

using CSocketStreamBuf = downloader::SocketStreamBuf;

std::string GetHeaders(std::iostream& ios);
std::size_t GetContentLength(const std::string& headers);

int main() {
  struct addrinfo* result = nullptr;
  struct addrinfo hints;
  int sock_fd;

  std::memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  if (getaddrinfo("192.168.22.251", "3128", &hints, &result) != 0) {
    return 1;
  }

  if (result != nullptr) {
    sock_fd = socket(result->ai_family, result->ai_socktype | SOCK_NONBLOCK,
                     result->ai_protocol);

    if (sock_fd == -1) {
      return 2;
    }
  }

  connect(sock_fd, result->ai_addr, result->ai_addrlen);

  fd_set client;
  FD_ZERO(&client);
  FD_SET(sock_fd, &client);

  int retval = select(sock_fd + 1, nullptr, &client, nullptr, nullptr);
  if (!retval) {
    std::cout << "cannot establish connection" << std::endl;

    return 3;
  }

  CSocketStreamBuf css;
  css.set_socket(sock_fd);
  std::iostream ios{&css};

  ios << "GET "
         "http://releases.ubuntu.com/14.04.5/ubuntu-14.04.5-desktop-amd64.iso "
         "HTTP/1.1"
      << std::endl;
  ios << "Host: releases.ubuntu.com" << std::endl << std::endl;

  auto HTTP_headers = GetHeaders(ios);
  std::cout << HTTP_headers << std::endl;

  auto content_len_bytes = GetContentLength(HTTP_headers);
  auto to_read = content_len_bytes;
  constexpr std::size_t data_size = 1024;
  std::array<char, data_size> data;

  std::cout << data.size() << std::endl;

  std::ofstream ofs{"file", std::ios_base::binary};
  auto rest_data_size = ios.readsome(data.begin(), to_read);

  ofs.write(data.begin(), rest_data_size);
  to_read -= rest_data_size;

  while (to_read && ios.read(data.begin(), data.size())) {
    to_read -= ios.gcount();
    ofs.write(data.begin(), ios.gcount());
  }

  if (ios.eof()) {
    std::cout << "end of file" << std::endl;
  }

  freeaddrinfo(result);
  close(css.get_socket());

  return 0;
}

std::string GetHeaders(std::iostream& ios) {
  constexpr auto init_storage_size = 65536U;
  std::string headers;
  bool http_header_delim_met = false;

  headers.reserve(init_storage_size);

  for (auto ch = '\0'; !http_header_delim_met && ios.get(ch);) {
    headers += ch;

    if (ch == '\r') {
      unsigned short counter = 1;

      while (counter < 4 && ios.get(ch) && (ch == '\r' || ch == '\n')) {
        ++counter;
        headers += ch;
      }

      if (counter == 4) {
        // remove additional '\r\n'
        headers.pop_back();
        headers.pop_back();
        http_header_delim_met = true;
      } else {
        ios.putback(ch);
      }
    }
  }

  headers.shrink_to_fit();

  return headers;
}

std::size_t GetContentLength(const std::string& headers) {
  std::size_t content_len = 0;
  const std::string cl_ = "Content-Length:";

  const auto pos = headers.find(cl_);

  if (pos != std::string::npos) {
    content_len = std::strtoul(&headers.front() + pos + cl_.size(), nullptr, 0);
  }

  return content_len;
}
