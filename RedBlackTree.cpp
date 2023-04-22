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
void RedBlackTree<T, M>::LeftRotation(Node<T, M> *X) {
  auto *Y = X->right_;
  auto *beta = Y->left_;
  auto *parent = X->parent_; // upper parent of X, not see in the picture

  if (this->size_ < 3 || X == nullptr || Y == nullptr || parent == nullptr ||
      beta == nullptr) {
    throw std::runtime_error("error in LeftRotation");
  }
  // init X - beta
  CreateRightEdge(X, beta);

  // init X - Y
  CreateLeftEdge(Y, X);

  // init upper parent - Y
  bool node_is_left = IsLeftSideOfNode(X);
  node_is_left ? CreateLeftEdge(parent, Y) : CreateRightEdge(parent, Y);
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
void RedBlackTree<T, M>::RightRotation(Node<T, M> *X) {
  // node is X
  auto *Y = X->parent_;
  auto *beta = X->right_;
  auto *parent = Y->parent_; // upper parent of Y

  if (this->size_ < 3 || X == nullptr || beta == nullptr || Y == nullptr ||
      parent == nullptr) {
    throw std::runtime_error("error in LeftRotation");
  }
  // init X - Y
  CreateRightEdge(X, Y);

  // init Y - beta
  CreateLeftEdge(Y, beta);

  // init upper parent - X
  bool node_is_left = IsLeftSideOfNode(Y);
  node_is_left ? CreateLeftEdge(parent, X) : CreateRightEdge(parent, X);
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
