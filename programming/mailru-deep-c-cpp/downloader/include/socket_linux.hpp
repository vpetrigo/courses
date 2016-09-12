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
  Socket* CreateSocket() override;
  Socket* CreateSecureSocket();
  ~LinuxSocketFactory() override = default;
};

}  // namespace downloader

#endif  // MAILRU_COURSE_SOCKET_LINUX_HPP
