add_executable(socket_linux_test socket_linux_test.cpp ${DOWNLOADER_INC})
target_link_libraries(socket_linux_test LinuxSocket gtest gtest_main)
