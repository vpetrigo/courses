cmake_minimum_required(VERSION 3.2)
project(downloader)

set(DOWNLOADER_LIBS downloader CACHE INTERNAL "")

include_directories(include/)

add_subdirectory(src)
add_subdirectory(examples)
