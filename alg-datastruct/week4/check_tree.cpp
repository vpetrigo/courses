#include "tree_traverse.hpp"

#include <algorithm>
#include <iostream>

int main()
{
    std::size_t n_nodes;
    std::vector<TreeNode> tree;

    std::cin >> n_nodes;

    for (std::size_t i = 0; i < n_nodes; ++i) {
        TreeNode node;

        std::cin >> std::get<0>(node) >> std::get<1>(node) >> std::get<2>(node);
        tree.emplace_back(std::move(node));
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
