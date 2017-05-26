#ifndef _COURSES_AVL_TREE_HPP_
#define _COURSES_AVL_TREE_HPP_

#include <algorithm>
#include <memory>

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
  using const_iterator = const _avl_node<T> *;

  AVL_Tree() : root_{nullptr} {}

  ~AVL_Tree()
  {
    if (root_ != nullptr) {
      PostOrderDelete(root_);
    }
  }

  AVL_Tree(const AVL_Tree& tree) = delete;
  AVL_Tree& operator=(const AVL_Tree& tree) = delete;

  AVL_Tree(AVL_Tree &&tree) noexcept : root_{std::move(tree.root_)} {}

  AVL_Tree &operator=(AVL_Tree &&tree) noexcept
  {
    root_ = std::move(tree.root_);

    return *this;
  }

  void Insert(const T &key) { root_ = Insert(root_, key); }

  void Remove(const T &key)
  {
    root_ = Remove(root_, key);
  }

  const T *Find(const T &key) const { return Find(root_, key); }

  int GetRootHeight() const { return GetNodeHeight(root_); }

 protected:
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

  iterator Remove(iterator hint, const T &key)
  {
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

  const T *Find(iterator hint, const T &key) const
  {
    const_iterator it = hint;

    while (it != nullptr && it->key_ != key) {
      it = (key < it->key_) ? it->left_child_ : it->right_child_;
    }

    return (it != nullptr) ? &it->key_ : nullptr;
  }

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

  iterator RightRotation(iterator node)
  {
    iterator left_child = node->left_child_;
    node->left_child_ = left_child->right_child_;
    left_child->right_child_ = node;
    FixHeight(node);
    FixHeight(left_child);

    return left_child;
  }

  iterator LeftRotation(iterator node)
  {
    iterator right_child = node->right_child_;
    node->right_child_ = right_child->left_child_;
    right_child->left_child_ = node;
    FixHeight(node);
    FixHeight(right_child);

    return right_child;
  }

  iterator FindMin(iterator node) const
  {
    iterator min_it = node;

    while (min_it->left_child_ != nullptr) {
      min_it = node->left_child_;
    }

    return min_it;
  }

  iterator RemoveMin(iterator node)
  {
    if (node->left_child_ == nullptr) {
      return node->right_child_;
    }

    node->left_child_ = RemoveMin(node->left_child_);

    return Balance(node);
  }

  unsigned GetNodeHeight(const_iterator node) const
  {
    return (node != nullptr) ? node->height_ : 0;
  }

  int BalanceFactor(const_iterator node) const
  {
    return static_cast<int>(GetNodeHeight(node->right_child_) -
                            GetNodeHeight(node->left_child_));
  }

  void FixHeight(iterator node)
  {
    const auto left_subtree_h = GetNodeHeight(node->left_child_);
    const auto right_subtree_h = GetNodeHeight(node->right_child_);

    node->height_ = std::max(left_subtree_h, right_subtree_h) + 1;
  }

  void PostOrderDelete(iterator node)
  {
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
