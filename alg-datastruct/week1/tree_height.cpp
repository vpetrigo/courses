#include "tree_height.hpp"

#include <algorithm>

std::size_t TreeHeight(const std::vector<int>& tree_parent_list)
{
  // root node has parent -1 in a tree parents list
  static constexpr int ROOT_NODE = -1;
  // init depth values for each node equal to zero
  std::vector<std::size_t> depth(tree_parent_list.size(), 0);

  for (std::size_t i = 0; i < tree_parent_list.size(); ++i) {
    std::size_t cur_depth = 1;
    std::size_t back_track_index = i;
    // backtrack through the parents either the root is reached or
    // previously calculated value is met
    while (tree_parent_list[back_track_index] != ROOT_NODE &&
           depth[back_track_index] == 0) {
      ++cur_depth;
      back_track_index =
          static_cast<std::size_t>(tree_parent_list[back_track_index]);
    }

    if (depth[back_track_index] != 0) {
      cur_depth += depth[back_track_index] - 1;
    }

    depth[i] = cur_depth;
  }

  return *std::max_element(depth.cbegin(), depth.cend());
}
