#include "phonebook.hpp"

#include <gtest/gtest.h>
#include <unordered_map>

TEST(Phonebook_HashTable, add_get_one_element)
{
    NumericHashTable ht;

    ht.Add(std::make_pair(1, "Test"));
    ASSERT_EQ(ht.Get(1), "Test");
}

TEST(Phonebook_HashTable, add_get_many_elements)
{
    NumericHashTable ht;
    constexpr std::size_t n_elements = 1024;

    for (std::size_t i = 0; i < n_elements; ++i) {
        ht.Add(std::make_pair(i, std::to_string(i)));
    }

    for (std::size_t i = 0; i < n_elements; ++i) {
        ASSERT_EQ(ht.Get(i), std::to_string(i));
    }
}

TEST(Phonebook_HashTable, add_get_1024_hash_10e5_elements)
{
    NumericHashTable ht{1024};
    constexpr std::size_t n_elements = 100000;

    for (std::size_t i = 0; i < n_elements; ++i) {
        ht.Add(std::make_pair(i, std::to_string(i)));
    }

    for (std::size_t i = 0; i < n_elements; ++i) {
        ASSERT_EQ(ht.Get(i), std::to_string(i));
    }
}

TEST(Phonebook_HashTable, single_key_multiple_requests)
{
    NumericHashTable ht;
    constexpr std::size_t n_queries = 100000;
    constexpr std::size_t key = 1;

    for (std::size_t i = 0; i < n_queries; ++i) {
        ht.Add(std::make_pair(key, "Test"));
    }

    for (std::size_t i = 0; i < n_queries; ++i) {
        ASSERT_EQ(ht.Get(key), "Test");
    }
}

TEST(Phonebook_HashTable, get_nonexistent_key)
{
    NumericHashTable ht;
    auto &value = ht.Get(2);

    value = "123";
    ASSERT_EQ(ht.Get(2), "123");
}

TEST(Phonebook_HashTable, delete_element)
{
    NumericHashTable ht;

    ht.Add(std::make_pair(1, "Test1"));
    ht.Add(std::make_pair(2, "Test2"));

    ASSERT_EQ(ht.Get(1), "Test1");
    ASSERT_EQ(ht.Get(2), "Test2");
    ht.Delete(1);
    ht.Delete(2);
    ASSERT_EQ(ht.Get(1), "");
    ASSERT_EQ(ht.Get(2), "");
}
