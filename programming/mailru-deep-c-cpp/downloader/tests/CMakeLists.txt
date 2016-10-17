include_directories(${DOWNLOADER_INC})

add_executable(socket_linux_test socket_linux_test.cpp ${DOWNLOADER_INC})
target_link_libraries(socket_linux_test LinuxSocket gtest gtest_main)

add_executable(socket_streambuf_test socket_streambuf_test.cpp
        ${DOWNLOADER_INC}/socket_streambuf.hpp)

target_link_libraries(socket_streambuf_test gtest gtest_main)
