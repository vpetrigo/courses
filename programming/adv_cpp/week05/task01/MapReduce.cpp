#include <cstddef>
#include <future>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <vector>

template <typename It, typename UnOp, typename BinOp>
auto process(It begin, It end, UnOp f1, BinOp f2)
    -> decltype(f2(f1(*begin), f1(*begin)))
{
    auto res = f1(*begin);

    while (++begin != end) {
        res = f2(res, f1(*begin));
    }

    return res;
}

template <typename It, typename UnOp, typename BinOp>
auto map_reduce(It begin, It end, UnOp f1, BinOp f2, std::size_t threads)
    -> decltype(f2(f1(*begin), f1(*begin)))
{
    using Type = decltype(process(begin, end, f1, f2));
    auto it_offset = std::distance(begin, end) / threads;
    std::vector<std::future<Type>> v;
    It cur_begin = begin;
    It cur_end = (threads > 1) ? std::next(cur_begin, it_offset) : end;

    for (auto i = 0; i < threads; ++i) {
        v.emplace_back(std::async(std::launch::async, process<It, UnOp, BinOp>,
                                  cur_begin, cur_end, f1, f2));
        cur_begin = cur_end;
        cur_end = (i + 2 != threads) ? std::next(cur_begin, it_offset) : end;
    }

    Type res = process(v.begin(), v.end(),
                       [](decltype(*v.begin()) f) { return f.get(); }, f2);

    return res;
}

int main()
{
    std::list<int> l{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    // параллельное суммирование в 3 потока
    auto sum = map_reduce(l.begin(), l.end(), [](int i) { return i; },
                          std::plus<int>(), 3);
    std::cout << "Sum: " << sum << std::endl;
    // проверка наличия чётных чисел в четыре потока
    auto has_even =
        map_reduce(l.begin(), l.end(), [](int i) { return i % 2 == 0; },
                   std::logical_or<bool>(), 4);
    std::cout << "Has even: " << has_even << std::endl;
    return 0;
}
