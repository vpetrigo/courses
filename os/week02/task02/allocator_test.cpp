#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "allocator.hpp"

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
                    (ALLOC_NUM * (ALLOC_NUM + 1)) / 2 - Allocator::get_allocation_overhead());
    }

    SECTION("allocate zero block")
    {
        REQUIRE_FALSE(allocator.alloc(0));
        auto free_space = allocator.get_free_places();
        REQUIRE(free_space.size() == 1);
        REQUIRE(free_space.front() == BUF_SIZE - Allocator::get_allocation_overhead());
    }

    delete[] mem;
}