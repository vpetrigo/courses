set(brackets_src brackets.cpp brackets.hpp)

add_executable(brackets ${brackets_src})

add_executable(brackets_test brackets_test.cpp)
target_link_libraries(brackets_test gtest gtest_main)
add_test(NAME ds_brackets_test COMMAND brackets_test)
