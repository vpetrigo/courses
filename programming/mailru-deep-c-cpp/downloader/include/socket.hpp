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
#include <exception>
#include <memory>

namespace downloader {

#if defined(WIN32) || defined(_WIN32) || \
    defined(__WIN32) && !defined(__CYGWIN__)
using Socket_t = SOCKET;
constexpr auto INVALID_VALUE = INVALID_SOCKET;
#else
using Socket_t = int;
constexpr auto INVALID_VALUE = -1;
#endif

enum class Protocols { tcp, udp };

enum class IpSupport { v4, v6, both };

class SocketException : public std::exception {};

class Socket {
 public:
  virtual ~Socket();

  Socket(const Socket &) = delete;
  Socket &operator=(const Socket &) = delete;

  Socket_t GetFd() const;

 protected:
  Socket();

  Socket(Socket_t sfd, bool is_block = true);

  Socket(Socket &&);
  Socket &operator=(Socket &&);

  void swap(Socket &) noexcept;

  // Data fields
  Socket_t sock_fd_;
  bool is_block;
};

// abstract factory for creating sockets
class SocketFactory {
 public:
  virtual std::unique_ptr<Socket> CreateSocket(int sf, int st, int prot) = 0;
  virtual ~SocketFactory() = default;
};

}  // namespace downloader

#endif  // MAILRU_COURSE_SOCKET_HPP
