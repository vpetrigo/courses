#include <tuple>
#include <type_traits>

template <int N, int M, typename ... Args>
auto to_pair(const std::tuple<Args...>& t) -> decltype(std::pair<typename std::decay<decltype(std::get<N>(t))>::type, typename std::decay<decltype(std::get<M>(t))>::type>(std::get<N>(t), std::get<M>(t))) {
    return std::make_pair(std::get<N>(t), std::get<M>(t));
}

template <std::size_t N, std::size_t M, typename T>
auto to_pair(const T& t) -> decltype(std::make_pair(std::get<N>(t), std::get<M>(t))) {
    return std::make_pair(std::get<M>(t), std::get<N>(t));
}