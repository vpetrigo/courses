#include <array>
#include <iostream>

template <int... Vals> struct IntList;

template <int H, int... T> struct IntList<H, T...> {
    static constexpr int Head{H};
    using Tail = IntList<T...>;
};

template <> struct IntList<> {
};

template <int H, typename TL> struct IntCons;

template <int H, int... Vals> struct IntCons<H, IntList<Vals...>> {
    using type = IntList<H, Vals...>;
};

template <int a, int b> struct Plus {
    static constexpr int value = a + b;
};

template <typename IL1, typename IL2, template <int, int> class Fun> struct Zip;

template <int... Vals1, int... Vals2, template <int, int> class Fun>
struct Zip<IntList<Vals1...>, IntList<Vals2...>, Fun> {
    using type = IntList<Fun<Vals1, Vals2>::value...>;
};

template <template <int...> class TL, int... Vals>
void print_int_list(TL<Vals...> &&tl)
{
    std::array<int, sizeof...(Vals)> a{Vals...};

    std::cout << "IntList<";
    for (auto it = a.cbegin(); it != a.cend(); ++it) {
        std::cout << *it;

        if (std::next(it) != a.cend()) {
            std::cout << ", ";
        }
    }
    std::cout << ">" << std::endl;
}

int main()
{
    // два списка одной длины
    using L1 = IntList<1, 2, 3, 4, 5>;
    using L2 = IntList<1, 3, 7, 7, 2>;

    // результат применения — список с поэлементными суммами
    using L3 = Zip<L1, L2, Plus>::type; // IntList<2, 5, 10, 11, 7>
    print_int_list(L3{});
    return 0;
}