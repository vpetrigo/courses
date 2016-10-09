#ifndef MAILRU_COURSE_SOCKET_HPP
#define MAILRU_COURSE_SOCKET_HPP

#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <netdb.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#endif
#include <memory>

namespace downloader {

#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
using Socket_t = SOCKET;
constexpr auto INIT_SOCK_VALUE = INVALID_SOCKET;
#else
using Socket_t = int;
constexpr auto INIT_SOCK_VALUE = -1;
#endif

enum class Protocols { tcp, udp };

// base class for further system-depended implementations
class ClientSocket {
 public:
  virtual ~ClientSocket() = default;
  virtual int Read(char *input_buf, std::size_t size) = 0;
  virtual bool Send(const char *output_buf, std::size_t size) = 0;
  virtual bool Connect(const std::string &host, const std::string &port) = 0;
  Socket_t GetSocketFd() const;

 protected:
  void SetSocketFd(Socket_t s);

 private:
  Socket_t sock_fd_{INIT_SOCK_VALUE};
};

// abstract factory for creating sockets
class SocketFactory {
 public:
  virtual std::unique_ptr<ClientSocket> CreateSocket(int sf, int st,
                                                     int prot) = 0;
  virtual ~SocketFactory() = default;
};

}  // namespace downloader

#endif  // MAILRU_COURSE_SOCKET_HPP
