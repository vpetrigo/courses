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

template <int N, int K = 0> struct Generate {
    using type =
        typename IntCons<K, typename Generate<N - 1, K + 1>::type>::type;
};

template <int K> struct Generate<0, K> {
    using type = IntList<>;
};

int main()
{
    using L1 = IntList<2, 3, 4>;
    using L2 = IntCons<1, L1>::type; // IntList<1,2,3,4>
    using L3 = Generate<5>::type;    // IntList<0,1,2,3,4>

    std::cout << L2::Head << std::endl;
    std::cout << L3::Head << std::endl;
}