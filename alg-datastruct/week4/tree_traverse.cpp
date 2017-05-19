#include "tree_traverse.hpp"

#include <algorithm>
#include <iostream>

int main()
{
  std::vector<TreeNode> tree;
  std::size_t n_nodes;

  std::cin >> n_nodes;

  while (n_nodes-- > 0) {
    TreeNode node;

    std::cin >> std::get<0>(node) >> std::get<1>(node) >> std::get<2>(node);

    tree.emplace_back(std::move(node));
  }

  TreeTraverse traverse{&tree};
  const auto& order = traverse.GetOrder();

  traverse.InOrder(tree.front());
  std::for_each(order.cbegin(), order.cend(),
                [](const std::size_t el) { std::cout << el << ' '; });
  std::cout << std::endl;
  traverse.CleanOrder();
  traverse.PreOrder(tree.front());
  std::for_each(order.cbegin(), order.cend(),
                [](const std::size_t el) { std::cout << el << ' '; });
  std::cout << std::endl;
  traverse.CleanOrder();
  traverse.PostOrder(tree.front());
  std::for_each(order.cbegin(), order.cend(),
                [](const std::size_t el) { std::cout << el << ' '; });
  std::cout << std::endl;
  traverse.CleanOrder();
}
