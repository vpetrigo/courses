#include <algorithm>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

int main()
{
    using Task = std::pair<int, int>;

    std::vector<Task> tasks;
    int id = 0;
    int n;

    std::cin >> n;

    tasks.reserve(n);
    std::istream_iterator<int> it{std::cin};
    std::istream_iterator<int> sent{};
    std::transform(it, sent, std::back_inserter(tasks), [&id](const int &elem) {
        return std::make_pair(elem, id++);
    });
    std::sort(tasks.begin(), tasks.end());
    std::for_each(tasks.cbegin(), tasks.cend(),
                  [](const auto &task) { std::cout << task.second << " "; });

    return 0;
}