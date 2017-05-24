cxx_gtest(tree_traverse_test tree_traverse_test.cpp tree_traverse.hpp)
add_executable(tree_traverse_example tree_traverse.cpp tree_traverse.hpp)

add_executable(check_tree_example check_tree.cpp)

cxx_gtest(check_tree_strict_test check_tree_strict_test.cpp check_tree_strict.hpp)
add_executable(check_tree_strict_example check_tree_strict.hpp check_tree_strict.cpp)

cxx_gtest(avl_tree_test avl_tree_test.cpp avl_tree.hpp)
add_executable(avl_tree_example avl_tree.cpp avl_tree.hpp)
