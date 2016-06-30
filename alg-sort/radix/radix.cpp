#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

template <typename ForwardIt>
std::vector<unsigned int> radix_sort(ForwardIt begin, ForwardIt end, int base = 2);

template <typename T>
T get_digit(const T num, const int div, const int base);

template <typename T>
std::size_t get_num_len(T num) {
    std::size_t length = 0;

    while (num) {
        num >>= 1;
        ++length;
    }

    return length;
}

int main() {
    int n, base;
    std::cin >> n >> base;
    std::vector<unsigned int> input_num(n);

    for (auto& e : input_num) {
        std::cin >> e;
    }

    radix_sort(input_num.begin(), input_num.end());

    return 0;
}

template <typename ForwardIt>
std::vector<unsigned> radix_sort(ForwardIt begin, ForwardIt end, int base) {
    std::vector<unsigned> count(base);
    std::vector<unsigned int> sorted(begin, end);
    std::vector<unsigned int> temp(sorted.size(), 0);
    int div = 1;
    auto max_len = get_num_len(*std::max_element(begin, end));
    
    while (max_len > 0) {
        for (auto it = sorted.begin(); it != sorted.end(); ++it) {
            ++count[get_digit(*it, div, base)];
        }
        
        int cur_shift = 0;
        for (std::size_t i = 0; i < base; ++i) {
            cur_shift += std::exchange(count[i], cur_shift); 
        }

        for (auto it = sorted.begin(); it != sorted.end(); ++it) {
            auto num_pos = get_digit(*it, div, base);
            temp[count[num_pos]] = *it; 
            ++count[num_pos];
        }

        std::swap(sorted, temp);
        div *= base;
        --max_len;
        std::for_each(count.begin(), count.end(), [](unsigned& e) { e = 0; });
    }

    return sorted;
}

template <typename T>
T get_digit(const T num, const int div, const int base) {
    return num / div % base;
}

