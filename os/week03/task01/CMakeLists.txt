cmake_minimum_required(VERSION 3.5)
project(simple_scheduler)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wall)

add_executable(simple_scheduler simple_scheduler.cpp)