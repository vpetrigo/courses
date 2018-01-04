#include <iostream>
#include <cassert>

struct Struct {
    std::size_t size = 0;
};

template <typename T>
auto get_size(const T& t) -> decltype(t.size)
{
    return t.size;
}

template <typename T>
auto get_size(const T& t) -> decltype(t.size())
{
    return t.size();
}

int main()
{
    std::string s{"Hello"};
    Struct x{10};

    assert(get_size(s) == s.size());
    assert(get_size(x) == x.size);

    return 0;
}
