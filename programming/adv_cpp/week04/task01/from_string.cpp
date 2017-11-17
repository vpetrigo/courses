#include <iostream>
#include <sstream>
#include <exception>
#include <typeinfo>

struct bad_from_string : std::exception {
    explicit bad_from_string(const std::string& what_arg) : what_arg_{what_arg} {}
    explicit bad_from_string(const char *what_arg) : what_arg_{what_arg} {}
    const char *what() const noexcept override {
        return what_arg_.c_str();
    }
private:
    std::string what_arg_;
};

template <typename T>
T from_string(const std::string& var) {
    std::istringstream iss{var};
    T out;

    iss >> std::noskipws >> out;

    if (iss.fail()) {
        throw bad_from_string{typeid(T).name()};
    }

    if (iss.get() && !iss.eof()) {
        throw bad_from_string{typeid(T).name()};
    }

    return out;
}

int main()
{
    std::string s1("123");
    int    a1 = from_string<int>   (s1); // a1 = 123
    double b1 = from_string<double>(s1); // b1 = 123.0
    std::string c1 = from_string<std::string>(s1); // c1 = "123"
    char d1 = from_string<char>(s1); // c1 = "123"

    std::string s2("12.3");
    int    a2;
    try {
        a2 = from_string<int>   (s2); // исключение
    }
    catch (const bad_from_string& e) {
        std::cerr << e.what() << std::endl;
    }
    double b2 = from_string<double>(s2); // b2 = 12.3
    std::string c2 = from_string<std::string>(s2); // c2 = "12.3"

    std::cout << a1 << " " << b1 << " " << c1 << std::endl;
    std::cout << a2 << " " << b2 << " " << c2 << std::endl;

    //std::string s3{"123123 123123"};
    //char c3 = from_string<char>(s3);
    //std::string d4 = from_string<std::string>(s3);

    //std::cout << int(c3) << std::endl;

    return 0;
}