#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

int main() {
    int n, base;

    std::cin >> n >> base;
    
    std::istream_iterator<unsigned int> it{std::cin};
    std::istream_iterator<unsigned int> sent;
    std::vector<unsigned int> inp(it, sent);

    std::sort(inp.begin(), inp.end());

    return 0;
}
