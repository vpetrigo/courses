add_executable(basic_sock_buf sock.cpp)

set_property(TARGET basic_sock_buf PROPERTY CXX_STANDARD 14)
set_property(TARGET basic_sock_buf PROPERTY CXX_STANDARD_REQUIRED ON)

add_executable(basic_sock_buf_proxy sock_proxy.cpp)

set_property(TARGET basic_sock_buf_proxy PROPERTY CXX_STANDARD 14)
set_property(TARGET basic_sock_buf_proxy PROPERTY CXX_STANDARD_REQUIRED ON)
