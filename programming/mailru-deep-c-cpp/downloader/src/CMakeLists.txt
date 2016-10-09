add_library(LinuxSocket socket.cpp socket_linux.cpp
        ${DOWNLOADER_INC}/socket.hpp
        ${DOWNLOADER_INC}/socket_linux.hpp)