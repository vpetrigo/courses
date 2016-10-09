#include <gtest/gtest.h>
#include "socket.hpp"
#include "socket_linux.hpp"

namespace dl = downloader;

TEST(Socket_Linux_Test, create_socket) {
  dl::LinuxTCPClientSocket s;

  s.Connect("www.google.com", "80");
  ASSERT_NE(s.GetSocketFd(), -1);
}
