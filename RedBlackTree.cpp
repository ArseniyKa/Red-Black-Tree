#include "RedBlackTree.h"
#include <string>

template <typename T, typename M> RedBlackTree<T, M>::RedBlackTree() {
  qDebug() << "Red Black tree constructor";
}

template <typename T, typename M> RedBlackTree<T, M>::~RedBlackTree() {
  qDebug() << "Red Black tree destructor";
}

//======================================
///@brief before left rotation:
//                 X
//       alpha             Y
//                   beta /// gama

///@brief after left rotation:
//                    Y
//          X        ///   gama
//   alpha // beta
//======================================
template <typename T, typename M>
void RedBlackTree<T, M>::LeftRotation(Node<T, M> *node) {
  // node is X
  auto *right_child = node->right_;                     // Y
  auto *left_child_of_right_child = right_child->left_; // beta
  auto *parent = node->parent_; // upper parent, not see in the picture

  if (this->size_ < 3 || node == nullptr || right_child == nullptr ||
      parent == nullptr || left_child_of_right_child == nullptr) {
    throw std::runtime_error("error in LeftRotation");
  }
  // init X - beta
  CreateRightEdge(node, left_child_of_right_child);

  // init X - Y
  CreateLeftEdge(right_child, node);

  // init upper parent - Y
  bool node_is_left = IsLeftSideOfNode(node);
  node_is_left ? CreateLeftEdge(parent, right_child)
               : CreateRightEdge(parent, right_child);
}

//======================================
///@brief after left rotation:
//                    Y
//          X        ///   gama
//   alpha // beta

///@brief before left rotation:
//                 X
//       alpha             Y
//                   beta /// gama
//======================================
template <typename T, typename M>
void RedBlackTree<T, M>::RightRotation(Node<T, M> *node) {
  // node is X
  auto *parent = node->parent_;        // Y
  auto *right_child = node->right_;    // beta
  auto *grandfather = parent->parent_; // upper parent

  if (this->size_ < 3 || node == nullptr || right_child == nullptr ||
      parent == nullptr || grandfather == nullptr) {
    throw std::runtime_error("error in LeftRotation");
  }
  // init X - Y
  CreateRightEdge(node, parent);

  // init Y - beta
  CreateLeftEdge(parent, right_child);

  // init upper parent - X
  bool node_is_left = IsLeftSideOfNode(parent);
  node_is_left ? CreateLeftEdge(grandfather, node)
               : CreateRightEdge(grandfather, node);
}

template <typename T, typename M>
void RedBlackTree<T, M>::CreateLeftEdge(Node<T, M> *upper_node,
                                        Node<T, M> *lower_node) {
  upper_node->left_ = lower_node;
  lower_node->parent_ = upper_node;
}

template <typename T, typename M>
void RedBlackTree<T, M>::CreateRightEdge(Node<T, M> *upper_node,
                                         Node<T, M> *lower_node) {
  upper_node->right_ = lower_node;
  lower_node->parent_ = upper_node;
}

// explicit instantiation
template class RedBlackTree<int, std::string>;
