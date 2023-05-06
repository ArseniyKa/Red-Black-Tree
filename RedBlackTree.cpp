#include "RedBlackTree.h"
#include <string>

template <typename T, typename M> RedBlackTree<T, M>::RedBlackTree() {
  //  qDebug() << "Red Black tree constructor";
}

template <typename T, typename M> RedBlackTree<T, M>::~RedBlackTree() {
  //  qDebug() << "Red Black tree destructor";
}

template <typename T, typename M>
bool RedBlackTree<T, M>::IsLeftSideOfNode(Node<T, M> *node) {
  if (node == nullptr) {
    throw std::runtime_error("error in IsLeftSide. Node is nullptr");
  }

  if (node->value_ == this->root_->value_) {
    throw std::runtime_error("error in IsLeftSide. root doesn't have parent");
  }

  auto *parent = node->parent_;
  if (parent == nullptr) {
    throw std::runtime_error("error in IsLeftSide. parent is nullptr");
  }

  auto *left_parent_child = parent->left_;
  auto *right_parent_child = parent->right_;

  auto key = node->key_;

  if (left_parent_child != nullptr && key == left_parent_child->key_) {
    return true;
  } else if (right_parent_child != nullptr && key == right_parent_child->key_) {
    return false;
  } else {
    throw std::runtime_error("error in IsLeftSide. No one accepted condition");
  }

  return false;
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

  // init upper parent - Y
  bool node_is_left = IsLeftSideOfNode(X);

  if (this->size_ < 3 || X == nullptr || Y == nullptr || parent == nullptr) {
    throw std::runtime_error("error in LeftRotation");
  }
  // init X - beta
  CreateRightEdge(X, beta);

  // init X - Y
  CreateLeftEdge(Y, X);

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

  // init upper parent - X
  bool node_is_left = IsLeftSideOfNode(Y);

  if (this->size_ < 3 || X == nullptr || beta == nullptr || Y == nullptr ||
      parent == nullptr) {
    throw std::runtime_error("error in LeftRotation");
  }
  // init X - Y
  CreateRightEdge(X, Y);

  // init Y - beta
  CreateLeftEdge(Y, beta);

  node_is_left ? CreateLeftEdge(parent, X) : CreateRightEdge(parent, X);
}

template <typename T, typename M>
void RedBlackTree<T, M>::recolor(RBNode<T, M> *node) {
  if (node == nullptr || node->parent_ == nullptr) {
    throw std::runtime_error("Error in recolor()");
  }

  auto color = node->color_;
  if (color == Color::Undefined) {
    throw std::runtime_error(
        "Error in recolor(): color was previously undefined");
  }

  if (node->value_ == this->root_->value_) {
    return;
  }

  bool is_black_color = color == Color::Black;
  node->color_ = is_black_color ? Color::Red : Color::Black;
}

template <typename T, typename M>
void RedBlackTree<T, M>::insert(T key, M value) {
  this->BinaryTree<T, M>::insert(key, value); // simple insert a node
  if (this->size_ == 1) {
    TreeEmtyCase(key, value);
    return;
  }

  auto *rb_node = GetRBNode(this->find(key));
  auto *parent = GetRBNode(rb_node->parent_);

  this->CheckNode(parent, "Error in insert() method");
  if (parent->color_ == Color::Red) {
    RedParentCase(rb_node);
    return;
  }
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
  if (lower_node == nullptr) {
    upper_node->right_ = nullptr;
    return;
  }
  upper_node->right_ = lower_node;
  lower_node->parent_ = upper_node;
}

template <typename T, typename M>
void RedBlackTree<T, M>::TreeEmtyCase(T key, M value) {
  if (this->size_ != 1 || this->root_ == nullptr) {
    throw std::runtime_error("Error in TreeEmtyCase()");
  }

  auto rb_node = dynamic_cast<RBNode<T, M> *>(this->root_);
  rb_node->color_ = Color::Black;
}

template <typename T, typename M>
void RedBlackTree<T, M>::CreateNewNode(T key, M value, Node<T, M> *&node,
                                       Node<T, M> *parent) {

  if (node != nullptr) {
    throw std::runtime_error("Error in CreateNewNode() method");
  }

  node = new RBNode<T, M>;
  node->key_ = key;
  node->value_ = value;
  node->parent_ = parent;

  auto *rb_node = dynamic_cast<RBNode<T, M> *>(node);
  rb_node->color_ =
      Color::Red; // по умолчанию всегда выставляется сначала красный цвет
  this->size_++;
}

template <typename T, typename M>
RBNode<T, M> *RedBlackTree<T, M>::GetUncle(Node<T, M> *node) {
  this->CheckNode(node, "Error in GetUncle(): node is nullptr");
  auto *parent = node->parent_;
  this->CheckNode(parent, "Error in GetUncle(): parent is nullptr");
  auto *grandfather = parent->parent_;
  this->CheckNode(grandfather, "Error in GetUncle(): grandfather is nullptr");

  bool is_left_node = this->IsLeftSideOfNode(parent);
  // if parent is on left side uncle should be on right side
  auto *uncle = is_left_node ? grandfather->right_ : grandfather->left_;
  auto *rb_uncle = dynamic_cast<RBNode<T, M> *>(uncle);
  return rb_uncle;
}

template <typename T, typename M>
Color RedBlackTree<T, M>::GetColor(Node<T, M> *node) const {
  this->CheckNode(node, "Error in GetColor(): node is nullptr");
  auto *rb_node = GetRBNode(node);
  return rb_node->color_;
}

template <typename T, typename M>
RBNode<T, M> *RedBlackTree<T, M>::GetRBNode(Node<T, M> *node) const {
  this->CheckNode(node, "Error in GetRBNode() method, node is nullptr");
  return dynamic_cast<RBNode<T, M> *>(node);
}

template <typename T, typename M>
void RedBlackTree<T, M>::RedParentRedUncleCase(RBNode<T, M> *node) {
  auto *parent = dynamic_cast<RBNode<T, M> *>(node->parent_);
  auto *uncle = GetUncle(node);
  auto *grandfather = dynamic_cast<RBNode<T, M> *>(parent->parent_);

  this->CheckNode(node,
                  "Error in ParentUncleAreRedCase() method, parent is nullptr");
  this->CheckNode(node,
                  "Error in ParentUncleAreRedCase() method, uncle is nullptr");
  this->CheckNode(
      node, "Error in ParentUncleAreRedCase() method, grandfather is nullptr");

  recolor(parent);
  recolor(uncle);
  if (grandfather->value_ != this->root_->value_) {
    recolor(grandfather);
  }
}

template <typename T, typename M>
void RedBlackTree<T, M>::RedParentBlackUncleCase(RBNode<T, M> *node) {
  this->CheckNode(node, "Error in ParentRedUncleBlackCase(): node is nullptr");
  auto *uncle = GetUncle(node);
  auto *parent = GetRBNode(node->parent_);
  bool is_parent_right = !IsLeftSideOfNode(parent);
  bool is_node_right = !IsLeftSideOfNode(node);
  if (is_parent_right && is_node_right) {
    RightParentRightNodeCase(node);
  } else if (is_parent_right && !is_node_right) {
    RightParentLeftNodeCase(node);
  } else if (!is_parent_right && !is_node_right) {
    LeftParentLeftNodeCase(node);
  } else if (!is_parent_right && is_node_right) {
    LeftParentRightNodeCase(node);
  }
}

template <typename T, typename M>
void RedBlackTree<T, M>::RightParentRightNodeCase(RBNode<T, M> *node) {
  this->CheckNode(
      node, "Error in ParentRightChildNodeRightChildCase(): node is nullptr");
  auto *parent = node->parent_;
  this->CheckNode(
      parent,
      "Error in ParentRightChildNodeRightChildCase(): parent is nullptr");
  auto *grandparent = parent->parent_;
  this->CheckNode(
      grandparent,
      "Error in ParentRightChildNodeRightChildCase(): grandparent is nullptr");

  LeftRotation(grandparent);
  recolor(GetRBNode(grandparent));
  recolor(GetRBNode(parent));
}

template <typename T, typename M>
void RedBlackTree<T, M>::RightParentLeftNodeCase(RBNode<T, M> *node) {
  this->CheckNode(node, "Error in RightParentLeftNodeCase(): node is nullptr");
  auto *parent = node->parent_;
  this->CheckNode(node,
                  "Error in RightParentLeftNodeCase(): parent is nullptr");
  RightRotation(node);
  RightParentRightNodeCase(GetRBNode(parent));
}

template <typename T, typename M>
void RedBlackTree<T, M>::LeftParentLeftNodeCase(RBNode<T, M> *node) {

  this->CheckNode(node, "Error in LeftParentLeftNodeCase(): node is nullptr");
  auto *parent = node->parent_;
  this->CheckNode(parent,
                  "Error in LeftParentLeftNodeCase(): parent is nullptr");
  auto *grandparent = parent->parent_;
  this->CheckNode(grandparent,
                  "Error in LeftParentLeftNodeCase(): grandparent is nullptr");
  RightRotation(parent);
  recolor(GetRBNode(grandparent));
  recolor(GetRBNode(parent));
}

template <typename T, typename M>
void RedBlackTree<T, M>::LeftParentRightNodeCase(RBNode<T, M> *node) {
  this->CheckNode(node, "Error in RightParentLeftNodeCase(): node is nullptr");
  auto *parent = node->parent_;
  this->CheckNode(node,
                  "Error in RightParentLeftNodeCase(): parent is nullptr");
  LeftRotation(parent);
  LeftParentLeftNodeCase(GetRBNode(parent));
}

template <typename T, typename M>
void RedBlackTree<T, M>::RedParentCase(RBNode<T, M> *node) {
  this->CheckNode(node, "Error in RedParentCase(): node is nullptr");

  auto *uncle = GetUncle(node);
  if (uncle != nullptr && uncle->color_ == Color::Red) {
    RedParentRedUncleCase(node);
  } else if (uncle == nullptr || uncle->color_ == Color::Black) {
    RedParentBlackUncleCase(node);
  } else if (uncle->color_ == Color::Undefined) {
    throw std::runtime_error(
        "Error in RedParentCase():Uncle color is Undefined");
  }
}

// explicit instantiation
template class RedBlackTree<int, std::string>;
