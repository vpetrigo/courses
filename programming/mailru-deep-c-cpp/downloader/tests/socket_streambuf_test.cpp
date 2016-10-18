#include <gtest/gtest.h>
#include "socket_streambuf.hpp"
#include <iostream>

TEST(SockStreamBuf_test, const_char_input) {
  downloader::Char_SockStreambuf sb(512);
  std::iostream ios(&sb);
  const char *s = "Hello";
  std::string cs;

  ios << s;
  ios >> cs;
  ASSERT_STREQ(s, cs.c_str());
}

TEST(SockStreamBuf_test, unsigned_char_input) {
  constexpr std::size_t size = 4;
  downloader::Char_SockStreambuf sb(size);
  std::iostream ios(&sb);
  const char *s = "\xff\xff\xff\xff";
  unsigned char out[size];

  ios << s;
  char ch = '\0';
  for (std::size_t i = 0; ios.get(ch); ++i) {
    out[i] = static_cast<unsigned char> (ch);
    EXPECT_EQ(out[i], static_cast<unsigned char>('\xff'));
  }
}

TEST(SockStreamBuf_test, commit_seq) {
  constexpr std::size_t size = 32;
  downloader::Char_SockStreambuf sb(32);
  std::string s{"Hello"};
  auto write_area = sb.prepare(s.size());
  auto s_it = s.cbegin();

  for (auto it = write_area.first; it != write_area.second; it = std::next(it)) {
    *it = *s_it;
    s_it = std::next(s_it);
  }

  sb.commit(std::distance(write_area.first, write_area.second));

  std::istream is{&sb};
  std::string s_c;

  is >> s_c;

  EXPECT_EQ(s, s_c);
}
