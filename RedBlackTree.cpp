#include "RedBlackTree.h"
#include <string>

template <typename T, typename M> RedBlackTree<T, M>::RedBlackTree() {
  //  qDebug() << "Red Black tree constructor";
}

template <typename T, typename M> RedBlackTree<T, M>::~RedBlackTree() {
  //  qDebug() << "Red Black tree destructor";
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

  this->CheckNode(parent, __func__, "parent");
  if (parent->color_ == Color::Red) {
    RedParentCase(rb_node);
    return;
  }
}

template <typename T, typename M> void RedBlackTree<T, M>::remove(T key) {
  auto *node = this->find(key);
  auto *left_child = GetRBNode(node->left_);
  auto *right_child = GetRBNode(node->right_);

  int child_number = 0;
  (left_child == nullptr) ? child_number = child_number : child_number++;
  (right_child == nullptr) ? child_number = child_number : child_number++;

  if (child_number == 0) {
    ZeroLeavesRemoveCase_new(node);
  } else if (child_number == 1) {
    OneLeafRemoveCase(node);
  }
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

  if (X->key_ != this->root_->key_) {
    // init upper parent - Y
    bool node_is_left = this->IsLeftSideOfNode(X);
    node_is_left ? this->CreateLeftEdge(parent, Y)
                 : this->CreateRightEdge(parent, Y);
  } else {
    this->root_ = Y;
    Y->parent_ = nullptr;
  }

  if (this->size_ < 3 || X == nullptr || Y == nullptr) {
    this->ErrorMessage("Error in LeftRotation()");
  }
  // init X - beta
  this->CreateRightEdge(X, beta);

  // init X - Y
  this->CreateLeftEdge(Y, X);
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
  bool node_is_left = this->IsLeftSideOfNode(Y);

  if (this->size_ < 3 || X == nullptr || Y == nullptr || parent == nullptr) {
    this->ErrorMessage("Error in RightRotation()");
  }
  // init X - Y
  this->CreateRightEdge(X, Y);

  // init Y - beta
  this->CreateLeftEdge(Y, beta);

  node_is_left ? this->CreateLeftEdge(parent, X)
               : this->CreateRightEdge(parent, X);
}

template <typename T, typename M>
void RedBlackTree<T, M>::recolor(RBNode<T, M> *node) {
  if (node == nullptr ||
      (node->parent_ == nullptr && node->key_ != this->root_->key_)) {
    this->ErrorMessage("Error in recolor()");
  }

  auto color = node->color_;
  CheckColor(color);

  if (node->key_ == this->root_->key_) {
    node->color_ = Color::Black;
    return;
  }

  bool is_black_color = color == Color::Black;
  node->color_ = is_black_color ? Color::Red : Color::Black;
}

template <typename T, typename M>
void RedBlackTree<T, M>::TreeEmtyCase(T key, M value) {
  if (this->size_ != 1 || this->root_ == nullptr) {
    this->ErrorMessage("Error in TreeEmtyCase()");
  }

  auto rb_node = dynamic_cast<RBNode<T, M> *>(this->root_);
  rb_node->color_ = Color::Black;
}

template <typename T, typename M>
void RedBlackTree<T, M>::CreateNewNode(T key, M value, Node<T, M> *&node,
                                       Node<T, M> *parent) {

  if (node != nullptr) {
    this->ErrorMessage("Error in CreateNewNode(): node should be nullptr");
  }

  node = new RBNode<T, M>;
  node->key_ = key;
  node->value_ = value;
  node->parent_ = parent;

  auto *rb_node = GetRBNode(node);
  // по умолчанию всегда выставляется сначала красный цвет
  rb_node->color_ = Color::Red;
  this->size_++;
}

template <typename T, typename M>
RBNode<T, M> *RedBlackTree<T, M>::GetUncle(Node<T, M> *node) {
  this->CheckNode(node, __func__, "node");
  auto *parent = node->parent_;
  this->CheckNode(parent, __func__, "parent");
  auto *grandfather = parent->parent_;
  this->CheckNode(grandfather, __func__, "grandfather");

  bool is_left_node = this->IsLeftSideOfNode(parent);
  // if parent is on left side uncle should be on right side
  auto *uncle = is_left_node ? grandfather->right_ : grandfather->left_;

  ///@note  uncle can be nullptr
  auto *rb_uncle = dynamic_cast<RBNode<T, M> *>(uncle);
  return rb_uncle;
}

template <typename T, typename M>
RBNode<T, M> *RedBlackTree<T, M>::GetRBNode(Node<T, M> *node) const {
  this->CheckNode(node, __func__, "node");
  return dynamic_cast<RBNode<T, M> *>(node);
}

template <typename T, typename M>
void RedBlackTree<T, M>::RedParentRedUncleCase(RBNode<T, M> *node) {

  this->CheckNode(node, __func__, "parent");
  auto *parent = dynamic_cast<RBNode<T, M> *>(node->parent_);
  this->CheckNode(parent, __func__, "parent");
  auto *uncle = GetUncle(node);
  this->CheckNode(uncle, __func__, "uncle");
  auto *grandfather = dynamic_cast<RBNode<T, M> *>(parent->parent_);
  this->CheckNode(grandfather, __func__, "grandfather");

  recolor(parent);
  recolor(uncle);
  if (grandfather->value_ != this->root_->value_) {
    recolor(grandfather);
    auto rb_grandfather_father = GetRBNode(grandfather->parent_);
    // проделать первые шаги для дедушки если его отец красный
    if (rb_grandfather_father->color_ == Color::Red) {
      RedParentCase(grandfather);
    }
  }
}

template <typename T, typename M>
void RedBlackTree<T, M>::RedParentBlackUncleCase(RBNode<T, M> *node) {
  this->CheckNode(node, __func__, "node");
  auto *uncle = GetUncle(node);
  auto *parent = GetRBNode(node->parent_);
  bool is_parent_right = !this->IsLeftSideOfNode(parent);
  bool is_node_right = !this->IsLeftSideOfNode(node);
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
  this->CheckNode(node, __func__, "node");
  auto *parent = node->parent_;
  this->CheckNode(parent, __func__, "parent");
  auto *grandparent = parent->parent_;
  this->CheckNode(grandparent, __func__, "grandparent");

  LeftRotation(grandparent);
  recolor(GetRBNode(grandparent));
  recolor(GetRBNode(parent));
}

template <typename T, typename M>
void RedBlackTree<T, M>::RightParentLeftNodeCase(RBNode<T, M> *node) {
  this->CheckNode(node, __func__, "node");
  auto *parent = node->parent_;
  this->CheckNode(parent, __func__, "parent");
  RightRotation(node);
  RightParentRightNodeCase(GetRBNode(parent));
}

template <typename T, typename M>
void RedBlackTree<T, M>::LeftParentLeftNodeCase(RBNode<T, M> *node) {
  this->CheckNode(node, __func__, "node");
  auto *parent = node->parent_;
  this->CheckNode(parent, __func__, "parent");
  auto *grandparent = parent->parent_;
  this->CheckNode(grandparent, __func__, "grandparent");

  RightRotation(parent);
  recolor(GetRBNode(grandparent));
  recolor(GetRBNode(parent));
}

template <typename T, typename M>
void RedBlackTree<T, M>::LeftParentRightNodeCase(RBNode<T, M> *node) {
  this->CheckNode(node, __func__, "node");
  auto *parent = node->parent_;
  this->CheckNode(parent, __func__, "parent");

  LeftRotation(parent);
  LeftParentLeftNodeCase(GetRBNode(parent));
}

template <typename T, typename M>
void RedBlackTree<T, M>::CheckColor(const Color color) {
  if (color == Color::Undefined) {
    throw std::runtime_error(
        "Error in recolor(): color was previously undefined");
  }
}

template <typename T, typename M>
void RedBlackTree<T, M>::ZeroLeavesRemoveCase_new(Node<T, M> *&node) {
  this->CheckNode(node, __func__, "node");

  if (node->left_ != nullptr || node->right_ != nullptr) {
    this->ErrorMessage("Error in removeZeroLeavesCase()");
  }

  auto color = GetRBNode(node)->color_;
  if (color == Color::Red) {
    this->AllLeavesEmptyCase((node));
  } else if (color == Color::Black) {
    this->ErrorMessage("Error in removeZeroLeavesCase(): Not resolved yet");
  } else {
    this->ErrorMessage("Error in removeZeroLeavesCase(): Undefined color");
  }
}

template <typename T, typename M>
void RedBlackTree<T, M>::OneLeafRemoveCase(Node<T, M> *&node) {
  this->CheckNode(node, __func__, "node");

  auto rb_node = GetRBNode(node);
  if (rb_node->color_ != Color::Black) {
    this->ErrorMessage("Error in removeOneLeafCase(): node should be black");
  }

  if (node->left_ != nullptr && node->right_ != nullptr ||
      node->left_ == nullptr && node->right_ == nullptr) {
    this->ErrorMessage("Error in removeOneLeafCase()");
  }

  auto *child = (node->left_ != nullptr) ? node->left_ : node->right_;
  auto child_color = GetRBNode(child)->color_;

  if (child_color != Color::Red) {
    this->ErrorMessage("Error in removeOneLeafCase(): child should be red");
  }

  BinaryTree<T, M>::remove(node->key_);
  this->CheckNode(child, __func__, "child");
  auto *rb_child = GetRBNode(child);
  rb_child->color_ = Color::Black;
}

template <typename T, typename M>
void RedBlackTree<T, M>::TwoLeavesRemoveCase(Node<T, M> *&node) {}

template <typename T, typename M>
Node<T, M> *RedBlackTree<T, M>::OneLeafEmptyCase(Node<T, M> *&node) {
  this->CheckNode(node, __func__, "node");
  if ((node->left_ != nullptr && node->right_ != nullptr) ||
      (node->left_ == nullptr && node->right_ == nullptr)) {
    this->ErrorMessage("Error in OneLeafEmptyCase(): should be one child");
  }

  bool is_left_child = node->left_ != nullptr;
  auto child = is_left_child ? node->left_ : node->right_;
  auto rb_child = GetRBNode(child);
  rb_child->color_ = Color::Black;

  return this->OneLeafEmptyCase(node);
}

template <typename T, typename M>
Node<T, M> *RedBlackTree<T, M>::AllLeavesEmptyCase(Node<T, M> *&node) {
  this->CheckNode(node, __func__, "node");
  if (node->left_ != nullptr || node->right_ != nullptr) {
    this->ErrorMessage("Error in AllLeavesEmptyCase(): shouldn't be any child");
  }

  auto rb_node = GetRBNode(node);
  auto color = rb_node->color_;

  if (color == Color::Red) {
    return this->AllLeavesEmptyCase(node);
  } else if (color == Color::Black) {
    this->ErrorMessage("Error in AllLeavesEmptyCase(): Not implemented yet");
  } else {
    this->ErrorMessage("Error in AllLeavesEmptyCase(): Undefined node color");
  }

  return nullptr;
}

template <typename T, typename M>
void RedBlackTree<T, M>::RedParentCase(RBNode<T, M> *node) {
  this->CheckNode(node, __func__, "node");

  // uncle can be nullptr
  auto *uncle = GetUncle(node);
  if (uncle != nullptr && uncle->color_ == Color::Red) {
    RedParentRedUncleCase(node);
  } else if (uncle == nullptr || uncle->color_ == Color::Black) {
    RedParentBlackUncleCase(node);
  } else {
    this->ErrorMessage("Error in RedParentCase()");
  }
}

// explicit instantiation
template class RedBlackTree<int, std::string>;
template class RedBlackTree<int, int>;
