#ifndef MAILRU_COURSE_PARSER_HPP
#define MAILRU_COURSE_PARSER_HPP

#include <string>

namespace downloader {

struct URLParser {
  explicit URLParser(const std::string &);
  explicit URLParser(const char *);

  std::string schema;
  std::string port;
  std::string host;
  std::string path;
  std::string query;
  std::string fragment;
  std::string filename;
  std::string username;
  std::string password;
};

}  // namespace downloader

#endif  // MAILRU_COURSE_PARSER_HPP
