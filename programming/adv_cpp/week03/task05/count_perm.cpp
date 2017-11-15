#include <iostream>
#include <algorithm>
#include <array>
#include <iterator>
#include <vector>

template <typename Iterator>
std::size_t count_permutations(Iterator p, Iterator q)
{
    using ItType = typename std::iterator_traits<Iterator>::value_type;

    if (p == q) {
        return 1;
    }

    std::vector<ItType> v(p, q);
    std::sort(v.begin(), v.end());
    std::size_t perm_count = (std::adjacent_find(v.cbegin(), v.cend()) == v.cend());

    while (std::next_permutation(v.begin(), v.end())) {
        if (std::adjacent_find(v.cbegin(), v.cend()) == v.cend()) {
            ++perm_count;
        }
    }

    return perm_count;
}

int main()
{
    std::array<int, 3> a{1, 2, 3};
    std::array<int, 5> b{1, 2, 3, 4, 4};
    std::array<int, 5> c{1, 2, 3, 4, 5};
    std::array<int, 5> d{5, 5, 5, 5, 5};
    std::array<int, 3> f{3, 1, 3};

    std::cout << count_permutations(a.cbegin(), a.cend()) << std::endl;
    std::cout << count_permutations(b.cbegin(), b.cend()) << std::endl;
    std::cout << count_permutations(c.cbegin(), c.cend()) << std::endl;
    std::cout << count_permutations(d.cbegin(), d.cend()) << std::endl;
    std::cout << count_permutations(f.cbegin(), f.cend()) << std::endl;

    return 0;
}