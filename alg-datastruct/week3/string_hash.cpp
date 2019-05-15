#include "string_hash.hpp"

#include <iostream>

int main()
{
    std::size_t bucket_size;
    std::size_t n_queries;
    std::string command;
    std::string data;

    std::cin >> bucket_size >> n_queries;

    HashSet<std::string> ht{bucket_size};

    while (n_queries-- > 0) {
        std::cin >> command;

        if (command.compare("add") == 0) {
            std::cin >> data;
            ht.Add(data);
        }
        else if (command.compare("check") == 0) {
            std::size_t bucket;

            std::cin >> bucket;
            auto check_pair = ht.Check(bucket);
            std::for_each(check_pair.first, check_pair.second,
                          [](const std::string &s) { std::cout << s << ' '; });
            std::cout << std::endl;
        }
        else if (command.compare("find") == 0) {
            std::cin >> data;
            if (ht.Find(data) != ht.End()) {
                std::cout << "yes";
            }
            else {
                std::cout << "no";
            }

            std::cout << std::endl;
        }
        else {
            std::cin >> data;
            ht.Delete(data);
        }
    }

    return 0;
}
