/*
 * Проблема: Высота дерева
 * Вычислить высоту данного дерева
 *
 * Вход: корневое дерево с вершинами {0, ... , n - 1},
 * заданное как последовательность parent(0), ... , parent(n - 1),
 * где parent(i) - родитель i-вершины
 *
 * Пример:
 *  Вход:
 *  5
 *  4 -1 4 1 1
 *  Выход:
 *  3
 *
 *  Вход:
 *  5
 *  -1 0 4 0 3
 *  Выход:
 *  4
 *
 */
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
