#include <iostream>

template <int... Vals> struct IntList;

template <int H, int... T> struct IntList<H, T...> {
    static constexpr int Head{H};
    using Tail = IntList<T...>;
};

template <> struct IntList<> {
};

template <typename TL>
struct Length {
    static constexpr std::size_t value = 1 +
        Length<typename TL::Tail>::value;
};

template <>
struct Length<IntList<>> {
    static constexpr std::size_t value = 0;
};

template <typename TL>
struct Length2;

template <template <int ...> class IntList, int ... Values>
struct Length2<IntList<Values...>> {
    static constexpr std::size_t value = sizeof...(Values);
};

int main() {
    using primes = IntList<2, 3, 5, 7, 11, 13>;

    std::cout << Length<primes>::value << std::endl;
    std::cout << Length2<primes>::value << std::endl;

    return 0;
}
