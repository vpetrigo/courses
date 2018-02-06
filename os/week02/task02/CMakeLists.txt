cmake_minimum_required(VERSION 3.5)
project(mem_alloc)

set(CMAKE_CXX_STANDARD 11)
set(catch2_inc "${CMAKE_CURRENT_LIST_DIR}/../../../deps/Catch2/single_include")
add_compile_options(-Wall)
enable_testing(true)

add_library(Catch2 INTERFACE)
target_include_directories(Catch2 INTERFACE ${catch2_inc})

add_executable(mem_alloc main.cpp allocator.hpp)
target_link_libraries(mem_alloc Catch2)

add_executable(allocator_test allocator_test.cpp allocator.hpp)
target_link_libraries(allocator_test Catch2)
add_test(NAME alloc_test COMMAND allocator_test)
