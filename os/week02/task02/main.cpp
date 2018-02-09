#include "allocator.hpp"

#include <cassert>
#include <iostream>

int main()
{
    std::cout << "Hello, World!" << std::endl;
    constexpr std::size_t BUF_SIZE = 100 * 1024;
    auto mem = new char[BUF_SIZE];
    Allocator allocator{mem, BUF_SIZE};

    std::cout << "Overhead: " << Allocator::get_allocation_overhead() << std::endl;
    auto free_places1 = allocator.get_free_places();

    for (const auto &e : free_places1)
    {
        std::cout << e << ' ';
    }

    std::cout << std::endl;
    auto ptr = static_cast<char *>(allocator.alloc(128));

    std::cout << static_cast<void *>(mem) << std::endl;
    std::cout << static_cast<void *>(ptr) << ' ' << static_cast<void *>(ptr - 32) << std::endl;
    auto free_places2 = allocator.get_free_places();
    for (const auto &e : free_places2)
    {
        std::cout << e << ' ';
    }

    std::cout << std::endl;
    delete[] mem;

    return 0;
}