#ifndef MAILRU_COURSE_SOCKET_LINUX_HPP
#define MAILRU_COURSE_SOCKET_LINUX_HPP

#include "socket.hpp"

namespace downloader {

class LinuxTCPClientSocket : public ClientSocket {
 public:
  LinuxTCPClientSocket();
  // deprecate copying of a socket
  LinuxTCPClientSocket(const LinuxTCPClientSocket&) = delete;
  LinuxTCPClientSocket &operator=(const LinuxTCPClientSocket&) = delete;
  // it might be possible to move socket
  LinuxTCPClientSocket(LinuxTCPClientSocket&&) = default;
  LinuxTCPClientSocket &operator=(LinuxTCPClientSocket&&) = default;

  ~LinuxTCPClientSocket() override;

  int Read(char *input_buf, std::size_t size) override;

  bool Send(const char *output_buf, std::size_t size) override;

  bool Connect(const std::string &host, const std::string &port) override;
};

class LinuxSocketFactory : public SocketFactory {
 public:
  std::unique_ptr<ClientSocket> CreateSocket(int sf, int st, int prot) override;
  std::unique_ptr<ClientSocket> CreateSecureSocket(int sf, int st, int prot);
  ~LinuxSocketFactory() override = default;
};

}  // namespace downloader

#endif  // MAILRU_COURSE_SOCKET_LINUX_HPP
