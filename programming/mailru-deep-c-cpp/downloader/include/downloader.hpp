#ifndef MAILRU_COURSE_DOWNLOADER_HPP
#define MAILRU_COURSE_DOWNLOADER_HPP

#include <memory>
#include <string>
#include "socket.hpp"

namespace downloader {
class Downloader {
 public:
  explicit Downloader(const std::string& url, const std::string& path = ".");
  ~Downloader();

  // prohibit copying
  Downloader(const Downloader&) = delete;
  Downloader& operator=(const Downloader&) = delete;
  // enalbe moving
  Downloader(Downloader&&) = default;
  Downloader& operator=(Downloader&&) = default;

  void SetDownloadLink(const std::string& url);
  void SetOutputPath(const std::string& path);
  void Download();

 private:
  std::unique_ptr<Socket> socket_;
  std::string url_;
  std::string output_path_;
};
}  // namespace downloader

#endif  // MAILRU_COURSE_DOWNLOADER_HPP
