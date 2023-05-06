#include "BinaryTree.h"
#include <iostream>

template <typename T, typename M> BinaryTree<T, M>::BinaryTree() {
  //  qDebug() << "BinaryTree constructor was called";
}

template <typename T, typename M> BinaryTree<T, M>::~BinaryTree() {
  //  qDebug() << "BinaryTree destructor was called";
}

template <typename T, typename M>
BinaryTree<T, M>::BinaryTree(const BinaryTree &other) {
  qDebug() << "BinaryTree copy constructor was called";
}

template <typename T, typename M>
BinaryTree<T, M> &BinaryTree<T, M>::operator=(const BinaryTree &other) {
  qDebug() << "BinaryTree copy assignment was called";
  return *this;
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
  } else if (key == root_->key_) {
    return root_;
  } else {
    throw std::runtime_error("undefined behavior in find()");
  }
}

template <typename T, typename M> void BinaryTree<T, M>::remove(T key) {
  auto *node = find(key);
  auto *parent = node->parent_;
  if (node->left_ == nullptr && node->right_ == nullptr) {
    AllLeavesEmptyCase(node);
  } else if (node->right_ == nullptr) {
    RightLeafEmptyCase(node);
  } else if (node->right_ != nullptr) {
    RightChildCase(node);
  } else {
    throw std::runtime_error("undefined behavior in remove()");
  }
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
    return node;
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
void BinaryTree<T, M>::NullParentLeaf(T key, Node<T, M> *parent) {
  if (parent->left_ != nullptr && key == parent->left_->key_) {
    parent->left_ = nullptr;
  } else if (parent->right_ != nullptr && key == parent->right_->key_) {
    parent->right_ = nullptr;
  } else {
    throw std::runtime_error("NullChildPointer error");
  }
}

template <typename T, typename M>
void BinaryTree<T, M>::AllLeavesEmptyCase(Node<T, M> *&node) {
  auto key = node->key_;
  auto *parent = node->parent_;
  NullParentLeaf(key, parent);
  delete node;
  size_--;
}

template <typename T, typename M>
void BinaryTree<T, M>::RightLeafEmptyCase(Node<T, M> *&node) {
  auto *parent = node->parent_;
  auto *left_child = node->left_;

  auto parent_key = parent->key_;
  auto key = node->key_;
  if (key < parent_key) {
    parent->left_ = left_child;
  } else {
    parent->right_ = left_child;
  }

  left_child->parent_ = parent;
  delete node;
  size_--;
}

template <typename T, typename M>
void BinaryTree<T, M>::RightChildCase(Node<T, M> *&node) {
  auto *right_child = node->right_;
  auto *left_grandson = right_child->left_;

  if (left_grandson == nullptr) {
    LeftGrandsonNull(node);
  } else {
    LeftGrandsonNotNull(node);
  }

  delete node;
  size_--;
}

template <typename T, typename M>
void BinaryTree<T, M>::LeftGrandsonNull(Node<T, M> *&node) {
  auto *parent = node->parent_;
  auto parent_key = parent->key_;
  auto key = node->key_;
  auto *right_child = node->right_;

  if (key < parent_key) {
    parent->left_ = right_child;
  } else {
    parent->right_ = right_child;
  }

  right_child->parent_ = parent;

  auto *left_child = node->left_;
  right_child->left_ = left_child;
  left_child->parent_ = right_child;
}

template <typename T, typename M>
void BinaryTree<T, M>::LeftGrandsonNotNull(Node<T, M> *&node) {
  auto *parent = node->parent_;
  auto parent_key = parent->key_;
  auto key = node->key_;
  auto *right_child = node->right_;
  auto *right_grandson = right_child->right_;

  auto min_child = FindMinimalSubTreeChild(right_child);
  if (key < parent_key) {
    parent->left_ = min_child;
  } else {
    parent->right_ = min_child;
  }

  min_child->parent_->left_ = nullptr;
  min_child->parent_ = parent;

  auto *left_child = node->left_;
  min_child->left_ = left_child;
  left_child->parent_ = min_child;

  min_child->right_ = right_child;
  right_child->parent_ = min_child;
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
void BinaryTree<T, M>::CheckNode(Node<T, M> *node,
                                 const std::string &error_message) const {
  if (node == nullptr) {
    throw std::runtime_error(error_message);
  }
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

// explicit instantiation
template class BinaryTree<int, char>;
template class BinaryTree<int, std::string>;
