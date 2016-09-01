add_library(disjoint_set STATIC disjoint_set.cpp)
set_property(TARGET disjoint_set PROPERTY CXX_STANDARD 14)
set_property(TARGET disjoint_set PROPERTY CXX_STANDARD_REQUIRED ON)

add_executable(clustering clustering.cpp)
target_link_libraries(clustering disjoint_set)
set_property(TARGET clustering PROPERTY CXX_STANDARD 14)
set_property(TARGET clustering PROPERTY CXX_STANDARD_REQUIRED ON)

add_executable(disjoint_set_test disjoint_set_test.cpp)
target_link_libraries(disjoint_set_test disjoint_set gtest gtest_main)
set_property(TARGET disjoint_set_test PROPERTY CXX_STANDARD 14)
set_property(TARGET disjoint_set_test PROPERTY CXX_STANDARD_REQUIRED ON)
