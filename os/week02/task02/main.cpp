#include "allocator.hpp"

#include <cassert>
#include <iostream>

static void print_allocator_mem(const Allocator &alloc)
{
    auto free_places = alloc.get_free_places();

    for (const auto &e : free_places)
    {
        std::cout << e << ' ';
    }

    std::cout << std::endl;
}

void test1()
{
    std::cout << "========= TEST1 ==========" << std::endl;
    constexpr std::size_t BUF_SIZE = 100 * 1024;
    char mem[BUF_SIZE];
    constexpr std::size_t ALLOC_NUM = 8;
    constexpr std::size_t ALLOC_SIZE = 128;
    std::vector<void *> mem_loc;
    Allocator allocator{mem, BUF_SIZE};

    for (std::size_t i = 0; i < ALLOC_NUM; ++i)
    {
        mem_loc.emplace_back(allocator.alloc(ALLOC_SIZE));
        assert(mem_loc.back() != nullptr);
    }

    print_allocator_mem(allocator);

    for (std::size_t i = 0; i < ALLOC_NUM; ++i)
    {
        if (i % 2 == 0)
        {
            std::cout << "Free (" << i << ") block" << std::endl;
            allocator.free(mem_loc[i]);
        }
    }

    print_allocator_mem(allocator);

    for (std::size_t i = 0; i < ALLOC_NUM; ++i)
    {
        if (i % 2 != 0)
        {
            std::cout << "Free (" << i << ") block" << std::endl;
            allocator.free(mem_loc[i]);
        }
    }

    print_allocator_mem(allocator);
    std::cout << "==========================" << std::endl;
}

void test2()
{
    std::cout << "========= TEST2 ==========" << std::endl;
    constexpr std::size_t BUF_SIZE = 100 * 1024;
    char mem[BUF_SIZE];
    constexpr std::size_t ALLOC_NUM = 3;
    constexpr std::size_t ALLOC_SIZE = 128;
    std::vector<void *> mem_loc;
    Allocator allocator{mem, BUF_SIZE};

    for (std::size_t i = 0; i < ALLOC_NUM; ++i)
    {
        mem_loc.emplace_back(allocator.alloc(ALLOC_SIZE));
        assert(mem_loc.back() != nullptr);
    }

    print_allocator_mem(allocator);

    for (std::size_t i = 0; i < ALLOC_NUM; ++i)
    {
        if (i % 2 == 0)
        {
            std::cout << "Free (" << i << ") block" << std::endl;
            allocator.free(mem_loc[i]);
        }
    }

    print_allocator_mem(allocator);

    for (std::size_t i = 0; i < ALLOC_NUM; ++i)
    {
        if (i % 2 != 0)
        {
            allocator.free(mem_loc[i]);
        }
    }

    print_allocator_mem(allocator);
    std::cout << "==========================" << std::endl;
}

int main()
{
    std::cout << "Hello, World!" << std::endl;
    constexpr std::size_t BUF_SIZE = 100 * 1024;
    auto mem = new char[BUF_SIZE];
    Allocator allocator{mem, BUF_SIZE};

    std::cout << "Overhead: " << Allocator::get_allocation_overhead()
              << std::endl;
    print_allocator_mem(allocator);
    auto ptr1 = static_cast<char *>(allocator.alloc(128));
    auto ptr2 = static_cast<char *>(allocator.alloc(128));
    auto ptr3 = static_cast<char *>(allocator.alloc(128));
    auto ptr4 = static_cast<char *>(allocator.alloc(128));

    std::cout << static_cast<void *>(mem) << std::endl;
    std::cout << static_cast<void *>(ptr1) << ' '
              << static_cast<void *>(ptr1 - 32) << std::endl;
    std::cout << static_cast<void *>(ptr2) << ' '
              << static_cast<void *>(ptr2 - 64 - 128 - 32) << std::endl;
    print_allocator_mem(allocator);
    allocator.free(ptr1);
    print_allocator_mem(allocator);
    allocator.free(ptr3);
    print_allocator_mem(allocator);
    allocator.free(ptr2);
    print_allocator_mem(allocator);
    allocator.free(ptr4);
    print_allocator_mem(allocator);
    delete[] mem;

    test1();
    test2();

    return 0;
}