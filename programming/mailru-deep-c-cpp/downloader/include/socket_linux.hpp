#ifndef MAILRU_COURSE_SOCKET_LINUX_HPP
#define MAILRU_COURSE_SOCKET_LINUX_HPP

#include "socket.hpp"

namespace downloader {

class LinuxSocket : public Socket {
 public:
  LinuxSocket(int sock_family, int sock_type, int protocol);
  // deprecate copying of a socket
  LinuxSocket(const LinuxSocket&) = delete;
  LinuxSocket& operator=(const LinuxSocket&) = delete;
  // it might be possible to move socket
  LinuxSocket(LinuxSocket&&) = default;
  LinuxSocket& operator=(LinuxSocket&&) = default;

  ~LinuxSocket() override;

  void ConnectSocket(const struct sockaddr* addr, socklen_t addrlen) override;
};

class LinuxSocketFactory : public SocketFactory {
 public:
  std::unique_ptr<Socket> CreateSocket(int sf, int st, int prot) override;
  std::unique_ptr<Socket> CreateSecureSocket(int sf, int st, int prot);
  ~LinuxSocketFactory() override = default;
};

}  // namespace downloader

#endif  // MAILRU_COURSE_SOCKET_LINUX_HPP
