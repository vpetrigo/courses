cmake_minimum_required(VERSION 3.2)

include_directories(deps/googletest/include)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(alg-graph)
add_subdirectory(alg-string)
add_subdirectory(alg-datastruct)
add_subdirectory(deps)

# Downloader project
add_subdirectory(programming/mailru-deep-c-cpp/downloader)
