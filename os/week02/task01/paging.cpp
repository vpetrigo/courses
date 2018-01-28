#include <array>
#include <iostream>
#include <unordered_map>

using UInt64 = unsigned long long;

template <typename T>
constexpr short get_mask(T num, unsigned pos, unsigned bit_mask)
{
    return (num >> pos) & ((1 << bit_mask) - 1);
}

template <typename T> constexpr T get_phy_addr(T reg)
{
    return (reg & (((1ULL << 40) - 1) << 12));
}

struct LogicalAddr {
  public:
    static std::array<short, 5> get_page(UInt64 addr)
    {
        return std::array<short, 5>{
            get_mask(addr, 39, 9), get_mask(addr, 30, 9), get_mask(addr, 21, 9),
            get_mask(addr, 12, 9), get_mask(addr, 0, 12)};
    }
};

auto get_memory_struct(std::size_t mem_pairs)
{
    std::unordered_map<UInt64, UInt64> mem;
    UInt64 paddr;
    UInt64 value;

    for (std::size_t i = 0; i < mem_pairs; ++i) {
        std::cin >> paddr >> value;
        mem[paddr] = value;
    }

    return mem;
}

std::pair<UInt64, bool>
logical_to_phy_addr(UInt64 laddr, std::size_t cr3,
                    const std::unordered_map<UInt64, UInt64> &mem)
{
    UInt64 value = cr3;
    auto page = LogicalAddr::get_page(laddr);

    for (std::size_t i = 0; i < page.size() - 1; ++i) {
        auto it = mem.find(page[i] * 8 + value);

        if (it == mem.end() || !(it->second & 1)) {
            return std::make_pair(0, false);
        }

        value = get_phy_addr(it->second);
    }

    return std::make_pair(value + page.back(), true);
}

void process_queries(std::size_t queries, std::size_t cr3,
                     const std::unordered_map<UInt64, UInt64> &mem)
{
    UInt64 addr;

    for (std::size_t i = 0; i < queries; ++i) {
        std::cin >> addr;

        auto phy_addr = logical_to_phy_addr(addr, cr3, mem);

        if (phy_addr.second) {
            std::cout << phy_addr.first << std::endl;
        }
        else {
            std::cout << "fault" << std::endl;
        }
    }
}

int main()
{
    std::size_t mem_pairs;
    std::size_t queries;
    std::size_t cr3;

    std::ios::sync_with_stdio(false);
    std::cin >> mem_pairs >> queries >> cr3;

    auto mem = get_memory_struct(mem_pairs);
    process_queries(queries, cr3, mem);

    return 0;
}
