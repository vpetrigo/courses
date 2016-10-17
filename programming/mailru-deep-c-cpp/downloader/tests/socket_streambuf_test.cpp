#include <gtest/gtest.h>
#include "socket_streambuf.hpp"
#include <iostream>

TEST(SockStreamBuf_test, const_char_input) {
  downloader::SockStreambuf<std::allocator<char>> sb(512);
  std::iostream ios(&sb);
  const char *s = "Hello";
  std::string cs;

  ios << s;
  ios >> cs;
  ASSERT_STREQ(s, cs.c_str());
}
