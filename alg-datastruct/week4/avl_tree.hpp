#ifndef _COURSES_AVL_TREE_HPP_
#define _COURSES_AVL_TREE_HPP_

#include <algorithm>
#include <memory>
#include <iostream>

template <typename T>
struct _avl_node {
  explicit _avl_node(T key) : key_{key} {}

  _avl_node *left_child_{nullptr};
  _avl_node *right_child_{nullptr};
  T key_;
  unsigned height_{1};
};

template <typename T>
class AVL_Tree {
 public:
  using iterator = _avl_node<T> *;

  AVL_Tree() : root_{nullptr} {}

  ~AVL_Tree() {
    if (root_ != nullptr) {
      PostOrderDelete(root_);
    }
  }

  iterator Insert(const T &key)
  {
    root_ = Insert(root_, key);

    return root_;
  }

  iterator Insert(iterator hint, const T &key)
  {
    if (hint == nullptr) {
      return new _avl_node<T>(key);
    }

    if (key < hint->key_) {
      hint->left_child_ = Insert(hint->left_child_, key);
    }
    else {
      hint->right_child_ = Insert(hint->right_child_, key);
    }

    return Balance(hint);
  }

  iterator Remove(const T& key) {
    if (root_ != nullptr) {
      return Remove(root_, key);
    }

    return nullptr;
  }

  iterator Remove(iterator hint, const T& key) {
    if (hint == nullptr) {
      return nullptr;
    }

    if (key < hint->key_) {
      hint->left_child_ = Remove(hint->left_child_, key);
    }
    else if (key > hint->key_) {
      hint->right_child_ = Remove(hint->right_child_, key);
    }
    else {
      auto left = hint->left_child_;
      auto right = hint->right_child_;

      delete hint;

      if (right == nullptr) {
        return left;
      }

      auto min = FindMin(right);

      min->right_child_ = RemoveMin(right);
      min->left_child_ = left;

      return Balance(min);
    }

    return Balance(hint);
  }

  const T *Find(const T& key) const {
    return Find(root_, key);
  }

  const T *Find(iterator hint, const T& key) const {
    if (hint == nullptr) {
      return nullptr;
    }

    if (key < hint->key_) {
      return Find(hint->left_child_, key);
    }
    else if (key > hint->key_) {
      return Find(hint->right_child_, key);
    }

     return &hint->key_;
  }

  int GetRootHeight() const {
    return GetNodeHeight(root_);
  }
 protected:
  // balance
  iterator Balance(iterator node)
  {
    const auto height_diff = BalanceFactor(node);

    FixHeight(node);

    if (height_diff > 1) {
      // right-heavy tree
      const auto right_subtree_balance = BalanceFactor(node->right_child_);

      if (right_subtree_balance < 0) {
        // left-heavy right subtree - big left rotation
        node->right_child_ = RightRotation(node->right_child_);
      }
      // small left rotation
      return LeftRotation(node);
    }
    else if (height_diff < -1) {
      // left-heavy tree
      const auto left_subtree_balance = BalanceFactor(node->left_child_);

      if (left_subtree_balance > 0) {
        // right-heavy left subtree - big right rotation
        node->left_child_ = LeftRotation(node->left_child_);
      }
      // small right rotation
      return RightRotation(node);
    }
    // do not need to do balancing here
    return node;
  }

  iterator RightRotation(iterator node) {
    iterator left_child = node->left_child_;
    node->left_child_ = left_child->right_child_;
    left_child->right_child_ = node;
    FixHeight(node);
    FixHeight(left_child);

    return left_child;
  }

  iterator LeftRotation(iterator node) {
    iterator right_child = node->right_child_;
    node->right_child_ = right_child->left_child_;
    right_child->left_child_ = node;
    FixHeight(node);
    FixHeight(right_child);

    return right_child;
  }

  iterator FindMin(iterator node) {
    return (node->left_child_) ? FindMin(node->left_child_) : node;
  }

  iterator RemoveMin(iterator node) {
    if(node->left_child_ == nullptr) {
      return node->right_child_;
    }

    node->left_child_ = RemoveMin(node->left_child_);

    return Balance(node);
  }

  unsigned GetNodeHeight(iterator node) const {
    return (node != nullptr) ? node->height_ : 0;
  }

  int BalanceFactor(iterator node) const {
    return static_cast<int>(GetNodeHeight(node->right_child_) - GetNodeHeight(node->left_child_));
  }

  void FixHeight(iterator node) {
    const auto left_subtree_h = GetNodeHeight(node->left_child_);
    const auto right_subtree_h = GetNodeHeight(node->right_child_);

    node->height_ = std::max(left_subtree_h, right_subtree_h) + 1;
  }

  void PostOrderDelete(iterator node) {
    if (node->left_child_ != nullptr) {
      PostOrderDelete(node->left_child_);
    }

    if (node->right_child_ != nullptr) {
      PostOrderDelete(node->right_child_);
    }

    delete node;
  }
 private:
  _avl_node<T> *root_;
};

#endif  // _COURSES_AVL_TREE_HPP_
