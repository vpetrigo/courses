#include <iostream>
#include <tuple>

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

template <typename F, typename T, int... Is>
auto apply(F f, T &&t, IntList<Is...>) -> decltype(f(std::get<Is>(t)...))
{
    return f(std::get<Is>(t)...);
}

template <typename F, typename... T,
          typename Index = typename Generate<sizeof...(T)>::type>
auto apply(F f, const std::tuple<T...> &t) -> decltype(apply(f, t, Index()))
{
    return apply(f, t, Index());
}

int main()
{
    auto f = [](int x, double y, double z) { return x + y + z; };
    auto t = std::make_tuple(30, 5.0, 1.6); // std::tuple<int, double, double>
    auto res = apply(f, t);
    std::cout << res << std::endl;
}