#include "inet_socket.hpp"

namespace downloader {
InetSocket::InetSocket() : host{}, port{} {}

const std::string &InetSocket::GetHost() const { return host; }

const std::string &InetSocket::GetPort() const { return port; }
}
