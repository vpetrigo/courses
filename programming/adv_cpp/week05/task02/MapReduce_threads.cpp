#include <algorithm>
#include <functional>
#include <list>
#include <thread>
#include <vector>

#include <iostream>

template <typename It, typename UnOp, typename BinOp>
auto map_reduce(It begin, It end, UnOp f1, BinOp f2, std::size_t threads)
    -> decltype(f2(f1(*begin), f1(*begin)))
{
    using Type = decltype(f1(*begin));
    auto it_offset = std::distance(begin, end) / threads;
    std::vector<std::thread> v;
    std::vector<Type> getters(threads);
    It cur_begin = begin;
    It cur_end = (threads > 1) ? std::next(cur_begin, it_offset) : end;

    auto process = [&f1, &f2, &getters](It b, It e, std::size_t index) {
        auto res = f1(*b);

        while (++b != e) {
            res = f2(res, f1(*b));
        }

        getters[index] = res;
    };

    for (auto i = 0; i < threads; ++i) {
        v.emplace_back(std::thread(process, cur_begin, cur_end, i));
        cur_begin = cur_end;
        cur_end = (i + 2 != threads) ? std::next(cur_begin, it_offset) : end;
    }

    std::for_each(
        v.begin(), v.end(),
        [](typename std::vector<std::thread>::value_type &t) { t.join(); });

    Type res = getters.front();

    std::for_each(getters.begin() + 1, getters.end(),
                  [&res, &f2](const typename std::vector<Type>::value_type &r) {
                      res = f2(res, r);
                  });

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