cxx_gtest(build_heap_test build_heap_test.cpp build_heap.hpp)
add_executable(build_heap build_heap.cpp build_heap.hpp)

cxx_gtest(priority_queue_test priority_queue_test.cpp priority_queue.hpp)
add_executable(priority_queue_example priority_queue.cpp priority_queue.hpp)
