#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "allocator.hpp"

#include <algorithm>
#include <iterator>
#include <list>

TEST_CASE("allocator overhead check", "[allocator]")
{
    REQUIRE(Allocator::get_allocation_overhead() <= 64);
}

TEST_CASE("straightforward allocation", "[allocator]")
{
    constexpr std::size_t BUF_SIZE = 100 * 1024;
    auto mem = new char[BUF_SIZE];
    Allocator allocator{mem, BUF_SIZE};

    SECTION("allocate equal blocks that fully occupy all memory")
    {
        constexpr std::size_t ALLOC_NUM = 4;
        constexpr std::size_t ALLOC_SIZE =
            (BUF_SIZE - ALLOC_NUM * Allocator::get_allocation_overhead()) /
            ALLOC_NUM;
        for (auto i = 0ULL; i < ALLOC_NUM; ++i)
        {
            REQUIRE(allocator.alloc(ALLOC_SIZE));
        }

        REQUIRE_FALSE(allocator.alloc(1));
        REQUIRE_FALSE(allocator.alloc(ALLOC_SIZE));

        auto free_space = allocator.get_free_places();

        REQUIRE(free_space.size() == 1);
        REQUIRE(free_space.front() == 0);
    }

    SECTION("allocate a bigger block than the allocator may allocate")
    {
        REQUIRE_FALSE(allocator.alloc(BUF_SIZE * 2));
        auto free_space = allocator.get_free_places();
        REQUIRE(free_space.size() == 1);
        REQUIRE(free_space.front() ==
                BUF_SIZE - Allocator::get_allocation_overhead());
    }

    SECTION("allocate smaller blocks")
    {
        constexpr std::size_t START_ALLOC = 1;
        constexpr std::size_t ALLOC_NUM = 100;

        for (auto i = 1ULL; i <= ALLOC_NUM; ++i)
        {
            REQUIRE(allocator.alloc(START_ALLOC * i));
        }

        auto free_space = allocator.get_free_places();
        REQUIRE(free_space.size() == 1);
        REQUIRE(free_space.front() ==
                BUF_SIZE - ALLOC_NUM * Allocator::get_allocation_overhead() -
                    (ALLOC_NUM * (ALLOC_NUM + 1)) / 2 -
                    Allocator::get_allocation_overhead());
    }

    SECTION("allocate zero block")
    {
        REQUIRE_FALSE(allocator.alloc(0));
        auto free_space = allocator.get_free_places();
        REQUIRE(free_space.size() == 1);
        REQUIRE(free_space.front() ==
                BUF_SIZE - Allocator::get_allocation_overhead());
    }

    delete[] mem;
}

TEST_CASE("allocation with free", "[allocator]")
{
    constexpr std::size_t BUF_SIZE = 100 * 1024;
    auto mem = new char[BUF_SIZE];
    Allocator allocator{mem, BUF_SIZE};

    SECTION("allocate all memory as one block and free it")
    {
        constexpr auto ALLOC_SIZE =
            BUF_SIZE - Allocator::get_allocation_overhead();
        auto ptr = allocator.alloc(ALLOC_SIZE);
        auto free_space = allocator.get_free_places();

        REQUIRE(free_space.size() == 1);
        REQUIRE(free_space.front() == 0);
        REQUIRE(ptr != nullptr);
        allocator.free(ptr);
        free_space = allocator.get_free_places();
        REQUIRE(free_space.size() == 1);
        REQUIRE(free_space.front() == ALLOC_SIZE);
    }

    SECTION("allocate all memory in several blocks and free it")
    {
        constexpr std::size_t ALLOC_NUM = 4;
        constexpr std::size_t ALLOC_SIZE =
            (BUF_SIZE - ALLOC_NUM * Allocator::get_allocation_overhead()) /
            ALLOC_NUM;
        std::vector<void *> mem_loc;

        for (auto i = 0ULL; i < ALLOC_NUM; ++i)
        {
            mem_loc.emplace_back(allocator.alloc(ALLOC_SIZE));
        }

        auto free_space = allocator.get_free_places();

        REQUIRE(free_space.size() == 1);
        REQUIRE(free_space.front() == 0);
        REQUIRE(std::all_of(std::begin(mem_loc), std::end(mem_loc),
                            [](const void *ptr) { return ptr != nullptr; }));

        for (auto i = 0ULL; i < mem_loc.size(); ++i)
        {
            allocator.free(mem_loc[i]);
            free_space = allocator.get_free_places();
            REQUIRE(free_space.size() == 1);
            REQUIRE(free_space.front() ==
                    ALLOC_SIZE * (i + 1) +
                        Allocator::get_allocation_overhead() * i);
        }

        mem_loc.clear();
        free_space = allocator.get_free_places();
        REQUIRE(free_space.front() ==
                BUF_SIZE - Allocator::get_allocation_overhead());
    }

    SECTION("allocate memory partially (even number of allocations) and free")
    {
        constexpr std::size_t ALLOC_SIZE = 128;
        constexpr std::size_t ALLOC_NUM = 128;
        constexpr std::size_t RESULT_OCCUPATION =
            (ALLOC_NUM * (ALLOC_SIZE + Allocator::get_allocation_overhead()));
        std::vector<void *> mem_loc;

        for (auto i = 0ULL; i < ALLOC_NUM; ++i)
        {
            mem_loc.emplace_back(allocator.alloc(ALLOC_SIZE));
        }

        auto free_space = allocator.get_free_places();

        REQUIRE(free_space.size() == 1);
        REQUIRE(free_space.front() == BUF_SIZE -
                                          Allocator::get_allocation_overhead() -
                                          RESULT_OCCUPATION);
        REQUIRE(std::all_of(std::begin(mem_loc), std::end(mem_loc),
                            [](const void *ptr) { return ptr != nullptr; }));

        for (auto i = 0ULL; i < ALLOC_NUM; ++i)
        {
            if (i % 2 == 0)
            {
                allocator.free(mem_loc[i]);
            }
        }

        free_space = allocator.get_free_places();
        REQUIRE(free_space.size() == 1 + mem_loc.size() / 2);
        REQUIRE(
            std::all_of(std::begin(free_space) + 1, std::end(free_space),
                        [](std::size_t size) { return size == ALLOC_SIZE; }));
        REQUIRE(free_space.front() == BUF_SIZE -
                                          Allocator::get_allocation_overhead() -
                                          RESULT_OCCUPATION);

        for (auto i = 0ULL; i < ALLOC_NUM; ++i)
        {
            if (i % 2 != 0)
            {
                allocator.free(mem_loc[i]);
            }
        }

        free_space = allocator.get_free_places();
        REQUIRE(free_space.size() == 1);
        REQUIRE(free_space.front() ==
                BUF_SIZE - Allocator::get_allocation_overhead());
        mem_loc.clear();
    }

    SECTION("allocate memory partially (odd number of allocations) and free")
    {
        constexpr std::size_t ALLOC_SIZE = 128;
        constexpr std::size_t ALLOC_NUM = 3;
        constexpr std::size_t RESULT_OCCUPATION =
            (ALLOC_NUM * (ALLOC_SIZE + Allocator::get_allocation_overhead()));
        std::vector<void *> mem_loc;

        for (auto i = 0ULL; i < ALLOC_NUM; ++i)
        {
            mem_loc.emplace_back(allocator.alloc(ALLOC_SIZE));
        }

        auto free_space = allocator.get_free_places();

        REQUIRE(free_space.size() == 1);
        REQUIRE(free_space.front() == BUF_SIZE -
                                          Allocator::get_allocation_overhead() -
                                          RESULT_OCCUPATION);
        REQUIRE(std::all_of(std::begin(mem_loc), std::end(mem_loc),
                            [](const void *ptr) { return ptr != nullptr; }));

        for (auto i = 0ULL; i < ALLOC_NUM; ++i)
        {
            if (i % 2 == 0)
            {
                allocator.free(mem_loc[i]);
            }

            free_space = allocator.get_free_places();
        }

        free_space = allocator.get_free_places();
        REQUIRE(free_space.size() == 1 + mem_loc.size() / 2);
        REQUIRE(
            std::all_of(std::begin(free_space) + 1, std::end(free_space),
                        [](std::size_t size) { return size == ALLOC_SIZE; }));
        REQUIRE(free_space.front() ==
                BUF_SIZE - Allocator::get_allocation_overhead() * (ALLOC_NUM) -
                    (ALLOC_NUM - 1) * ALLOC_SIZE);

        for (auto i = 0ULL; i < ALLOC_NUM; ++i)
        {
            if (i % 2 != 0)
            {
                allocator.free(mem_loc[i]);
            }
        }

        free_space = allocator.get_free_places();
        REQUIRE(free_space.size() == 1);
        REQUIRE(free_space.front() ==
                BUF_SIZE - Allocator::get_allocation_overhead());
        mem_loc.clear();
    }

    SECTION("variable length allocation and free")
    {
        constexpr std::size_t ALLOC_NUM = 350;
        std::vector<void *> mem_loc(ALLOC_NUM);
        std::size_t i = 1;
        std::generate(std::begin(mem_loc), std::end(mem_loc),
                      [&i, &allocator] { return allocator.alloc(i++); });
        auto free_space = allocator.get_free_places();

        REQUIRE(free_space.size() == 1);
        REQUIRE(free_space.front() ==
                BUF_SIZE - Allocator::get_allocation_overhead() -
                    (ALLOC_NUM * Allocator::get_allocation_overhead() +
                     (ALLOC_NUM * (ALLOC_NUM + 1)) / 2));

        std::for_each(std::begin(mem_loc), std::end(mem_loc),
                      [&allocator](void *&ptr) { allocator.free(ptr); });
        free_space = allocator.get_free_places();
        REQUIRE(free_space.size() == 1);
        REQUIRE(free_space.front() ==
                BUF_SIZE - Allocator::get_allocation_overhead());
    }

    SECTION("allocate random blocks and free them")
    {
        std::vector<void *> mem_loc;

        while (true)
        {
            void *ptr = allocator.alloc(rand());

            if (ptr)
            {
                mem_loc.emplace_back(ptr);
            }
            else
            {
                break;
            }
        }

        for (std::size_t i = 0; i < mem_loc.size(); ++i)
        {
            allocator.free(mem_loc[i]);
        }

        mem_loc.clear();

        auto free_space = allocator.get_free_places();
        REQUIRE(free_space.size() == 1);
        REQUIRE(free_space.front() == BUF_SIZE - Allocator::get_allocation_overhead());
    }

    delete[] mem;
}

TEST_CASE("utilizing memory from allocator", "[allocator]")
{
    constexpr std::size_t BUF_SIZE = 100 * 1024;
    char mem[BUF_SIZE];
    Allocator allocator{mem, BUF_SIZE};

    SECTION("allocate memory for a string")
    {
        constexpr std::size_t ALLOC_SIZE = 128;
        auto buf = static_cast<char *>(allocator.alloc(ALLOC_SIZE));
        REQUIRE(buf != nullptr);
        std::fill(buf, buf + ALLOC_SIZE, 'a');
        REQUIRE(std::all_of(buf, buf + ALLOC_SIZE,
                            [](const char &ch) { return ch == 'a'; }));
        auto buf2 = static_cast<char *>(allocator.alloc(ALLOC_SIZE));
        REQUIRE(buf2 != nullptr);
        std::fill(buf2, buf2 + ALLOC_SIZE, 'b');
        REQUIRE(std::all_of(buf, buf + ALLOC_SIZE,
                            [](const char &ch) { return ch == 'a'; }));
        REQUIRE(std::all_of(buf2, buf2 + ALLOC_SIZE,
                            [](const char &ch) { return ch == 'b'; }));
        allocator.free(buf2);
        REQUIRE(std::all_of(buf, buf + ALLOC_SIZE,
                            [](const char &ch) { return ch == 'a'; }));
        allocator.free(buf);

        auto free_space = allocator.get_free_places();

        REQUIRE(free_space.size() == 1);
        REQUIRE(free_space.front() ==
                BUF_SIZE - Allocator::get_allocation_overhead());
    }

    SECTION("allocation for an int array")
    {
        constexpr std::size_t ALLOC_SIZE = 128;
        constexpr int NUM1 = 0xCAFEBABE;
        auto buf1 =
            static_cast<int *>(allocator.alloc(ALLOC_SIZE * sizeof(int)));
        std::fill(buf1, buf1 + ALLOC_SIZE, NUM1);
        REQUIRE(std::all_of(buf1, buf1 + ALLOC_SIZE,
                            [](const int &num) { return num == NUM1; }));

        auto free_space = allocator.get_free_places();
        REQUIRE(free_space.size() == 1);
        REQUIRE(free_space.front() ==
                BUF_SIZE - 2 * Allocator::get_allocation_overhead() -
                    ALLOC_SIZE * sizeof(int));
        allocator.free(buf1);
        free_space = allocator.get_free_places();
        REQUIRE(free_space.size() == 1);
        REQUIRE(free_space.front() ==
                BUF_SIZE - Allocator::get_allocation_overhead());
    }
}