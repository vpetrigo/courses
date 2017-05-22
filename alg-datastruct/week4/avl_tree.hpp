#ifndef _COURSES_AVL_TREE_HPP_
#define _COURSES_AVL_TREE_HPP_

#include <memory>

template <typename T>
struct _avl_node {
  explicit _avl_node(T key) : parent_{nullptr}, key_{key}, height_{0} {}
  _avl_node(T key, _avl_node *parent, unsigned height)
      : parent_{parent}, key_{key}, height_{height}
  {
  }

  _avl_node *parent_;
  _avl_node *left_child_{nullptr};
  _avl_node *right_child_{nullptr};
  T key_;
  unsigned height_;
};

template <typename T>
class AVL_Tree {
 public:
  using iterator = _avl_node *;

  AVL_Tree() : root_{nullptr} {}
  iterator Insert(const T &key)
  {
    if (root_ != nullptr) {
      iterator hint = root_;
    }
    else {
      root_ = new _avl_node(key);

      return root_;
    }
  }

  iterator Insert(iterator hint, const T &key)
  {
    if (hint == nullptr) {
      return hint;
    }

    if (key < hint->key_) {
      if (hint->left_child_ != nullptr) {
        return Insert(hint->left_child_, key);
      }

      hint->left_child_ = new _avl_node(key, hint, hint->height_ + 1);
      // balance
      return hint->left_child_;
    }
    else {
      if (hint->right_child_ != nullptr) {
        return Insert(hint->right_child_, key);
      }

      hint->right_child_ = new _avl_node(key, hint, hint->height_ + 1);
      // balance
      return hint->right_child_;
    }
  }

 protected:
  // balance
  void Balance(_avl_node *node)
  {
    const auto height_diff = BalanceFactor(node);

    if (height_diff > 1) {
      // right-heavy tree
      const auto right_subtree_balance = BalanceFactor(node->right_child_);

      if (right_subtree_balance < -1) {
        // left-heavy right subtree - big left rotation
      }
      else {
        // small left rotation
      }
    }
    else if (height_diff < -1) {
      // left-heavy tree
      const auto left_subtree_balance = BalanceFactor(node->left_child_);

      if (left_subtree_balance > 1) {

      }
      else {

      }
    }
  }

  int BalanceFactor(_avl_node *node) {
    const auto left_subtree_h =
        (node->left_child_) ? node->left_child_->height_ : 0;
    const auto right_subtree_h =
        (node->right_child_) ? node->right_child_->height_ : 0;

    return static_cast<int>(right_subtree_h - left_subtree_h);
  }
  // rotation
 private:
  _avl_node *root_;
};

#endif  // _COURSES_AVL_TREE_HPP_
