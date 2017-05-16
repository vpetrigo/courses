#include "rabin_karp.hpp"

#include <algorithm>
#include <iostream>

int main()
{
  std::string pattern;
  std::string text;

  std::cin >> pattern >> text;

  RabinKarp rk{pattern};
  const auto pattern_occur = rk.GetPatternOccurence(text);

  std::for_each(
      std::cbegin(pattern_occur), std::cend(pattern_occur),
      [](const std::size_t& occurence) { std::cout << occurence << ' '; });
  std::cout << std::endl;

  return 0;
}
