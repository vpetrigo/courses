#include <iterator>
#include <algorithm>
#include <vector>
#include <iostream>

// алгоритм должен работать с forward итераторами
// и возвращать итератор, который потом будет передан
// в метод erase соответствующего контейнера
template<class FwdIt>
FwdIt remove_nth(FwdIt p, FwdIt q, size_t n)
{
    return std::remove_if(p, q, [&n](decltype(*p) val) { return n-- == 0; });
}

int main() {
    std::vector<int> v = {0,1,2,3,4,5,6,7,8,9,10};
    //std::vector<int> v = {};
    v.erase(remove_nth(v.begin(), v.end(), 5), v.end());

    for (const auto& e : v) {
        std::cout << e << ' ';
    }
    std::cout << std::endl;

    return 0;
}