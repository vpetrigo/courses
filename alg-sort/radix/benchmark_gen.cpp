#include <iostream>
#include <random>
#include <fstream>

int main() {
    int n, base;

    std::cin >> n >> base;
    std::random_device rnd;
    std::mt19937 gen(rnd());
    std::uniform_int_distribution<unsigned int> dist;
    std::ofstream ofs{"bench.txt"};

    if (!ofs) {
        std::cerr << "Cannot open file" << std::endl;
        return 1;
    }
    
    ofs << n << ' ' << base << std::endl;

    for (std::size_t i = 0; i < n; ++i) {
        ofs << dist(gen) << ' ';
    }
    
    ofs << std::endl;

    return 0;
}
