include_directories(${DOWNLOADER_INC})

add_library(inet_lib inet_socket.cpp socket.cpp
        ${DOWNLOADER_INC}/inet_socket.hpp ${DOWNLOADER_INC}/socket.hpp)
