set(brackets_src brackets.cpp brackets.hpp)
add_executable(brackets ${brackets_src})
cxx_gtest(brackets_test brackets_test.cpp)

add_library(tree_height tree_height.cpp tree_height.hpp)
set(tree_height_test_src tree_height.hpp tree_height.cpp tree_height_test.cpp)
cxx_gtest(tree_height_test "${tree_height_test_src}")
add_executable(tree_height_example tree_height_full.cpp)
target_link_libraries(tree_height_example tree_height)

set(network_queue_test_src network_queue.h network_queue_test.cpp)
cxx_gtest(network_queue_test "${network_queue_test_src}")
add_executable(network_queue_example network_queue.cpp network_queue.h)

set(max_stack_test_src max_stack.hpp max_stack_test.cpp)
cxx_gtest(max_stack_test "${max_stack_test_src}")
add_executable(max_stack_example max_stack.cpp max_stack.hpp)

add_executable(frame_max_value_example frame_max_value.cpp)
