cmake_minimum_required(VERSION 3.2)

include_directories(deps/googletest/include)

set(CMAKE_CXX_STANDARD 14)

enable_testing()

function(cxx_gtest name src)
    add_executable(${name} "${src}")
    target_link_libraries(${name} gtest gtest_main)
    add_test(NAME gtest_${name} COMMAND ${name})
endfunction(cxx_gtest)

add_subdirectory(alg-graph)
add_subdirectory(alg-string)
add_subdirectory(alg-datastruct)
add_subdirectory(deps)

# Downloader project
add_subdirectory(programming/mailru-deep-c-cpp/downloader)
