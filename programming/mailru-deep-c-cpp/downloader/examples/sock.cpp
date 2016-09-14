#include "socket_buf.hpp"
#include <iostream>
#include <algorithm>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cstring>
#include <fstream>

using CSocketStreamBuf = downloader::SocketStreamBuf<wchar_t>;

int main() {
  struct addrinfo *result = nullptr;
  struct addrinfo hints;
  int sock_fd;

  std::memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;

  if (getaddrinfo("192.168.22.251", "3128", &hints, &result) != 0) {
    return 1;
  }

  if (result != nullptr) {
    sock_fd = socket(result->ai_family, result->ai_socktype | SOCK_NONBLOCK, result->ai_protocol);

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
  std::wiostream ios{&css};

  ios << "GET http://releases.ubuntu.com/16.04/ubuntu-16.04.1-desktop-amd64.iso HTTP/1.1" << std::endl;
  ios << "Host: releases.ubuntu.com" << std::endl << std::endl;
  
  wchar_t buf[4096];
  int content_len_bytes = 0;
  std::string content_len = "Content-Length";

  std::memset(buf, 0, sizeof buf);

  while (ios.getline(buf, 4096, '\n')) {
    auto buf_size = std::strlen(buf);    
    // remove trailing '\r'
    buf[buf_size - 1] = '\0';
    --buf_size;
    if (buf_size == 0) {
        break;
    }
    
    if (std::equal(content_len.cbegin(), content_len.cend(), buf, 
                   [](const wchar_t& a, const wchar_t& b) { return std::tolower(a) == std::tolower(b); })) {
      auto it = std::find(buf, buf + buf_size, ' ');
      content_len_bytes = std::stoi(std::string(it, buf + buf_size));
    }

    std::cout << buf << std::endl;
    std::memset(buf, 0, sizeof buf);
  }

  std::cout << ios.gcount() << std::endl;
  std::cout << ios.good() << std::endl;
  
  auto data_size = 1024;
  wchar_t *data = new wchar_t[data_size];
  std::memset(data, 0, data_size);
  std::ofstream ofs{"file.txt", std::ios_base::binary};
  int rest_data_size = ios.readsome(data, data_size);
  ofs.write(data, rest_data_size);
  std::cout << rest_data_size << std::endl;
  content_len_bytes -= rest_data_size;
  
  data_size = std::min(data_size, content_len_bytes);
  while (content_len_bytes && ios.read(data, data_size)) {
    content_len_bytes -= ios.gcount();
    ofs.write(data, ios.gcount());
    data_size = std::min(data_size, content_len_bytes);
  }

  if (ios.eof()) {
    std::cout << "end of file" << std::endl;
  }

  delete[] data;
  freeaddrinfo(result);
  close(sock_fd);

  return 0;
}
