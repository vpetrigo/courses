#include <iostream>
#include <typeinfo>

void print_values(std::ostream& os) {}

template <typename T, typename... Args>
void print_values(std::ostream& os, const T& val, const Args&... args) {
    os << typeid(val).name() << ": " << val << std::endl;
    print_values(os, args...);
}

int main() {
    print_values(std::cout, 1, 2.04, std::string{"Hello World!"});
    return 0;
}