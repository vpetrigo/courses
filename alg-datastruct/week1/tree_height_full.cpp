#include "tree_height.hpp"

#include <iostream>
#include <iterator>

int main()
{
  std::size_t n;
  // read parent list size
  std::cin >> n;
  // read parent list
  std::istream_iterator<int> cit{std::cin};
  std::istream_iterator<int> sent;
  std::vector<int> parent_list{cit, sent};

  std::cout << TreeHeight(parent_list) << std::endl;

  return 0;
}
