#include "check_tree_strict.hpp"

#include <algorithm>
#include <iostream>

int main()
{
  std::size_t n_nodes;
  constexpr auto init = std::make_tuple(std::make_pair(0, 0), -1, -1);

  std::cin >> n_nodes;

  std::vector<TreeNode> tree(n_nodes, init);

  for (std::size_t i = 0; i < n_nodes; ++i) {
    std::size_t cur_level = std::get<0>(tree[i]).second;
    TreeNode node;

    std::cin >> std::get<0>(tree[i]).first >> std::get<1>(tree[i]) >>
        std::get<2>(tree[i]);

    if (std::get<1>(tree[i]) != -1) {
      std::get<0>(tree[std::get<1>(tree[i])]).second = cur_level + 1;
    }

    if (std::get<2>(tree[i]) != -1) {
      std::get<0>(tree[std::get<2>(tree[i])]).second = cur_level + 1;
    }
  }

  if (n_nodes == 0) {
    std::cout << "CORRECT" << std::endl;
  }
  else {
    TreeTraverse traverse{&tree};

    traverse.InOrder(tree.front());
    const auto order = traverse.GetOrder();

    if (std::is_sorted(order.cbegin(), order.cend())) {
      std::cout << "CORRECT" << std::endl;
    }
    else {
      std::cout << "INCORRECT" << std::endl;
    }
  }

  return 0;
}
