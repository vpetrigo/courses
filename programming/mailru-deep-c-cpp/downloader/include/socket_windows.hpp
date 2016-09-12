#ifndef MAILRU_COURSE_SOCKET_WINDOWS_HPP
#define MAILRU_COURSE_SOCKET_WINDOWS_HPP

#include "socket.hpp"

namespace downloader {

class WindowsSocket : public Socket {
 public:
  WindowsSocket(int sock_family, int sock_type, int protocol);
  // deprecate copying of a socket
  WindowsSocket(const WindowsSocket&) = delete;
  WindowsSocket& operator=(const WindowsSocket&) = delete;
  // it might be possible to move socket
  WindowsSocket(WindowsSocket&&) = default;
  WindowsSocket& operator=(WindowsSocket&&) = default;

  ~WindowsSocket() override;

  void ConnectSocket(const struct sockaddr* addr, socklen_t addrlen) override;
};

class WindowsSocketFactory : public SocketFactory {
 public:
  std::unique_ptr<Socket> CreateSocket(int sf, int st, int prot) override;
  std::unique_ptr<Socket> CreateSecureSocket(int sf, int st, int prot);
  ~WindowsSocketFactory() override = default;
};

}  // namespace downloader

#endif  // MAILRU_COURSE_SOCKET_WINDOWS_HPP
