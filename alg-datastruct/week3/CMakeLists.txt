cxx_gtest(phonebook_test phonebook_test.cpp phonebook.hpp)
add_executable(phonebook_example phonebook.cpp phonebook.hpp)

cxx_gtest(string_hash_test string_hash_test.cpp string_hash.hpp)
add_executable(string_hash_example string_hash.cpp string_hash.hpp)
