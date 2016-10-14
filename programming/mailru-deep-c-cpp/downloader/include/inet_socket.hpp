#ifndef MAILRU_COURSE_INET_SOCKET_HPP
#define MAILRU_COURSE_INET_SOCKET_HPP

#include "socket.hpp"

namespace downloader {
class InetSocket : public Socket {
 public:
  virtual ~InetSocket() = default;

  const std::string& GetHost() const;

  const std::string& GetPort() const;

 protected:
  InetSocket();

  // Data fields
  const std::string& host;
  const std::string& port;
};
}

#endif  // MAILRU_COURSE_INET_SOCKET_HPP
