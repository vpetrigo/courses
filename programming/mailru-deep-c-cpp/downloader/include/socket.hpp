#ifndef MAILRU_COURSE_SOCKET_HPP
#define MAILRU_COURSE_SOCKET_HPP

#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#endif

namespace downloader {

// base class for further system-depended implementations
class Socket {
 public:
  virtual ~Socket() = default;

  virtual void ConnectSocket(const struct sockaddr *addr,
                             socklen_t addrlen) = 0;

 protected:
  Socket(int sock_family, int sock_type, int protocol);

  int sock_fd_{-1};
};

// abstract factory for creating sockets
class SocketFactory {
 public:
  virtual Socket *CreateSocket() = 0;
  virtual ~SocketFactory() = default;
};

}  // namespace downloader

#endif  // MAILRU_COURSE_SOCKET_HPP
