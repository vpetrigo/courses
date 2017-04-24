set(brackets_src brackets.cpp brackets.hpp)

add_executable(brackets ${brackets_src})

cxx_gtest(brackets_test brackets_test.cpp)

add_library(tree_height tree_height.cpp tree_height.hpp)

set(tree_height_test_src tree_height.hpp tree_height.cpp tree_height_test.cpp)
cxx_gtest(tree_height_test "${tree_height_test_src}")
