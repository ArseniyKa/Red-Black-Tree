#include "BinaryTree.h"
#include <iostream>

#define GETNAME(var) #var

template <typename T, typename M> BinaryTree<T, M>::~BinaryTree() {
  DestroyRecursive(root_);
  root_ = nullptr;
  size_ = 0;
}

template <typename T, typename M>
void BinaryTree<T, M>::insert(T key, M value) {
  if (root_ == nullptr) {
    CreateNewNode(key, value, root_, nullptr);
    return;
  }

  if (key < root_->key_) {
    SubInsert(key, value, root_->left_, root_);
  } else if (key > root_->key_) {
    SubInsert(key, value, root_->right_, root_);
  } else {
    root_->value_ = value;
  }
}

template <typename T, typename M> int64_t BinaryTree<T, M>::size() const {
  return size_;
}

template <typename T, typename M> Node<T, M> *&BinaryTree<T, M>::find(T key) {
  if (root_ == nullptr) {
    throw std::runtime_error("the tree is empty");
  }

  if (key < root_->key_) {
    return SubFind(key, root_->left_);
  } else if (key > root_->key_) {
    return SubFind(key, root_->right_);
  } else {
    return root_;
  }
}

template <typename T, typename M> void BinaryTree<T, M>::remove(T key) {
  auto *node = find(key);
  Node<T, M> *deleted_node = nullptr;

  // if only one node
  if (this->size_ == 1) {
    delete deleted_node;
    size_--;
    root_ = nullptr;
    return;
  }

  if (node->left_ == nullptr && node->right_ == nullptr) {
    deleted_node = AllLeavesEmptyCase(node);
  } else if (node->left_ != nullptr && node->right_ != nullptr) {
    deleted_node = AllLeavesCase(node);
  } else {
    deleted_node = OneLeafEmptyCase(node);
  }

  CheckNode(deleted_node, __func__, "deleted node");

  delete deleted_node;
  size_--;
}

template <typename T, typename M> void BinaryTree<T, M>::traverse() {
  SubTranverse(root_);
}

template <typename T, typename M>
void BinaryTree<T, M>::SubInsert(T key, M value, Node<T, M> *&node,
                                 Node<T, M> *parent) {
  // место где добавляется новый узел
  if (node == nullptr) {
    CreateNewNode(key, value, node, parent);
    return;
  }

  if (key < node->key_) {
    SubInsert(key, value, node->left_, node);
  } else if (key > node->key_) {
    SubInsert(key, value, node->right_, node);
  }
}

template <typename T, typename M>
Node<T, M> *&BinaryTree<T, M>::SubFind(T key, Node<T, M> *node) {
  if (node == nullptr) {
    throw std::runtime_error("the node is nullptr");
  }

  if (key < node->key_) {
    return SubFind(key, node->left_);
  } else if (key > node->key_) {
    return SubFind(key, node->right_);
  } else if (key == node->key_) {
    // место где присваивается узел
    return node; // NOLINT
  } else {
    throw std::runtime_error("undefined behavior in SubFind()");
  }
}

template <typename T, typename M>
void BinaryTree<T, M>::CreateNewNode(T key, M value, Node<T, M> *&node,
                                     Node<T, M> *parent) {

  if (node != nullptr) {
    throw std::runtime_error("Error in CreateNewNode() method");
  }

  node = new Node<T, M>;
  node->key_ = key;
  node->value_ = value;
  node->parent_ = parent;
  size_++;
}

template <typename T, typename M>
Node<T, M> *BinaryTree<T, M>::AllLeavesEmptyCase(Node<T, M> *&node) {
  CheckNode(node, __func__, "node");

  auto *parent = node->parent_;
  bool is_left_node = this->IsLeftSideOfNode(node);
  is_left_node ? parent->left_ = nullptr : parent->right_ = nullptr;
  return node;
}

template <typename T, typename M>
Node<T, M> *BinaryTree<T, M>::OneLeafEmptyCase(Node<T, M> *&node) {
  bool is_child_left = node->left_ != nullptr;
  if (is_child_left && node->right_ != nullptr) {
    ErrorMessage("error in OneLeafEmptyCase: right leaf should be nullptr");
  } else if (!is_child_left && node->left_ != nullptr) {
    ErrorMessage("error in OneLeafEmptyCase: left leaf should be nullptr");
  } else if (node->left_ == nullptr && node->right_ == nullptr) {
    ErrorMessage(
        "error in OneLeafEmptyCase: one of the leaft shouldn't be nullptr");
  }

  auto *child = is_child_left ? node->left_ : node->right_;
  ReasignParentChild(node, child);
  return node;
}

template <typename T, typename M>
Node<T, M> *BinaryTree<T, M>::AllLeavesCase(Node<T, M> *&node) {

  CheckNode(node->left_, __func__, "left child");
  CheckNode(node->right_, __func__, "right child");

  auto *min_child = FindMinimalSubTreeChild(node->right_);
  CopySuccessor(node, min_child);

  if (min_child->left_ != nullptr && min_child->right_ != nullptr) {
    ErrorMessage("Problem with AllLeavesCase");
  }

  bool empty_leaves =
      min_child->left_ == nullptr && min_child->right_ == nullptr;
  return empty_leaves ? AllLeavesEmptyCase(min_child)
                      : OneLeafEmptyCase(min_child);
}

template <typename T, typename M>
Node<T, M> *&BinaryTree<T, M>::FindMinimalSubTreeChild(Node<T, M> *&node) {
  if (node == nullptr) {
    throw std::runtime_error("FindMinimalSubTreeChild error");
  }

  if (node->left_ != nullptr) {
    if (node->left_->key_ > node->key_) {
      throw std::runtime_error("FindMinimalSubTreeChild wrong function using");
    }
    return FindMinimalSubTreeChild(node->left_);
  } else {
    return node;
  }
}

template <typename T, typename M>
Node<T, M> *BinaryTree<T, M>::FindLastTreeNode(Node<T, M> *node) {
  if (node == nullptr) {
    throw std::runtime_error("FindLastTreeNode() error");
  }
  if (node->right_ != nullptr) {
    return FindLastTreeNode(node->right_);
  } else {
    return node;
  }
}

template <typename T, typename M>
void BinaryTree<T, M>::SubTranverse(Node<T, M> *node) {
  if (node == nullptr) {
    return;
  }

  SubTranverse(node->left_);
  std::cout << node->key_ << "   " << node->value_ << "\n";
  SubTranverse(node->right_);
}

template <typename T, typename M>
void BinaryTree<T, M>::CreateLeftEdge(Node<T, M> *upper_node,
                                      Node<T, M> *lower_node) {
  CheckNode(upper_node, __func__, "upper_node");
  if (lower_node == nullptr) {
    upper_node->left_ = nullptr;
    return;
  }
  upper_node->left_ = lower_node;
  lower_node->parent_ = upper_node;
}

template <typename T, typename M>
void BinaryTree<T, M>::CreateRightEdge(Node<T, M> *upper_node,
                                       Node<T, M> *lower_node) {
  CheckNode(upper_node, __func__, "upper_node");
  if (lower_node == nullptr) {
    upper_node->right_ = nullptr;
    return;
  }
  upper_node->right_ = lower_node;
  lower_node->parent_ = upper_node;
}

template <typename T, typename M>
void BinaryTree<T, M>::CheckNode(Node<T, M> *node,
                                 const std::string &function_name,
                                 const std::string &node_name) const {

  if (node == nullptr) {
    throw std::runtime_error("Error in " + function_name + "(): " + node_name +
                             " is nullptr");
  }
}

template <typename T, typename M>
void BinaryTree<T, M>::ReasignParentChild(Node<T, M> *old_child,
                                          Node<T, M> *new_child) {
  CheckNode(old_child, __func__, "old_child");
  CheckNode(new_child, __func__, "new_child");
  auto *parent = old_child->parent_;
  CheckNode(parent, __func__, "parent");

  bool is_left_child = IsLeftSideOfNode(old_child);
  is_left_child ? parent->left_ = new_child : parent->right_ = new_child;

  new_child->parent_ = parent;
}

template <typename T, typename M>
void BinaryTree<T, M>::CopySuccessor(Node<T, M> *node, Node<T, M> *successor) {
  node->key_ = successor->key_;
  node->value_ = successor->value_;
}

template <typename T, typename M>
BinaryTreeIterator<T, M, BinaryTree<T, M>> BinaryTree<T, M>::begin() {
  auto *first_node = FindMinimalSubTreeChild(root_);
  BinaryTreeIterator<T, M, BinaryTree<T, M>> iter(this, first_node);
  return iter;
}

template <typename T, typename M>
BinaryTreeIterator<T, M, BinaryTree<T, M>> BinaryTree<T, M>::end() {
  if (end_node_ == nullptr) {
    end_node_ = new Node<T, M>;
    end_node_->key_ = 888;
    end_node_->value_ = '.';
    auto *last_node = FindLastTreeNode(root_);
    last_node->right_ = end_node_;
  }

  BinaryTreeIterator<T, M, BinaryTree<T, M>> iter(this, end_node_);
  return iter;
}

template <typename T, typename M> Node<T, M> *BinaryTree<T, M>::root() const {
  CheckNode(root_, __func__, "root");
  return root_;
}

template <typename T, typename M>
void BinaryTree<T, M>::ErrorMessage(const std::string &message) const {
  throw std::runtime_error(message);
}

template <typename T, typename M>
bool BinaryTree<T, M>::IsLeftSideOfNode(Node<T, M> *node) const {

  this->CheckNode(node, __func__, "node");

  //  if (node->key_ == this->root_->key_) {
  //    this->ErrorMessage("Error in IsLeftSideOfNode():  node = root");
  //  }

  auto *parent = node->parent_;
  this->CheckNode(parent, __func__, "parent");

  auto *left_parent_child = parent->left_;
  auto *right_parent_child = parent->right_;

  auto key = node->key_;

  if (left_parent_child != nullptr && key == left_parent_child->key_) {
    return true;
  } else if (right_parent_child != nullptr && key == right_parent_child->key_) {
    return false;
  } else {
    this->ErrorMessage(
        "Error in IsLeftSideOfNode(): No one accepted condition");
  }

  return false;
}

template <typename T, typename M>
void BinaryTree<T, M>::DestroyRecursive(Node<T, M> *node) {
  if (node) {
    DestroyRecursive(node->left_);
    DestroyRecursive(node->right_);
    delete node;
  }
}

// explicit instantiation
template class BinaryTree<int, char>;
template class BinaryTree<int, std::string>;
template class BinaryTree<int, int>;
