cmake_minimum_required(VERSION 3.5)
project(round_robin)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wall)

add_executable(round_robin round_robin.cpp)