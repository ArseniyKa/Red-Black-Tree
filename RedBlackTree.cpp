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
///@brief after right rotation:
//                    Y
//          X        ///   gama
//   alpha // beta

///@brief before right rotation:
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
RBNode<T, M> *RedBlackTree<T, M>::GetSibling(Node<T, M> *node) {
  this->CheckNode(node, __func__, "node");

  auto parent = node->parent_;
  this->CheckNode(parent, __func__, "parent");

  bool is_left_node = this->IsLeftSideOfNode(node);
  auto *sibling = is_left_node ? parent->right_ : parent->left_;
  return dynamic_cast<RBNode<T, M> *>(sibling);
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

  return BinaryTree<T, M>::OneLeafEmptyCase(node);
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
    return BinaryTree<T, M>::AllLeavesEmptyCase(node);
  } else if (color == Color::Black) {
    return DoubleBlackCase(node);
  } else {
    this->ErrorMessage("Error in AllLeavesEmptyCase(): Undefined node color");
  }

  return node;
}

template <typename T, typename M>
Node<T, M> *RedBlackTree<T, M>::DoubleBlackCase(Node<T, M> *node) {

  if (node->key_ == this->root_->key_) {
    this->ErrorMessage("error: root case");
  }

  auto *sibling = GetSibling(node);

  if (sibling->color_ == Color::Red) {
    return RedSiblingCase(node, sibling);
  } else if (sibling->color_ == Color::Black) {
    return BlackSiblingCase(node, sibling);
  } else {
    this->ErrorMessage("Error in DoubleBlackCase(): Undefined color");
  }

  return node;
}

template <typename T, typename M>
Node<T, M> *RedBlackTree<T, M>::RedSiblingCase(Node<T, M> *node,
                                               Node<T, M> *sibling) {

  bool is_left_sibling = this->IsLeftSideOfNode(sibling);

  auto *parent = GetRBNode(sibling->parent_);
  is_left_sibling ? RightRotation(sibling) : LeftRotation(sibling->parent_);

  recolor(parent);
  recolor(GetRBNode(sibling));

  auto *new_sibling = is_left_sibling ? parent->left_ : parent->right_;

  return BlackSiblingBlackNephew(GetRBNode(node), GetRBNode(new_sibling));
}

template <typename T, typename M>
Node<T, M> *RedBlackTree<T, M>::BlackSiblingCase(Node<T, M> *node,
                                                 Node<T, M> *sibling) {
  auto *rb_node = GetRBNode(node);
  auto *rb_sibling = GetRBNode(sibling);
  auto sibling_color = rb_sibling->color_;
  auto *left_sibl_child = GetRBNode(rb_sibling->left_);
  auto *right_sibl_child = GetRBNode(rb_sibling->right_);

  bool is_left_child_null = left_sibl_child == nullptr;
  bool is_right_child_null = right_sibl_child == nullptr;

  auto left_child_color =
      is_left_child_null ? Color::Undefined : left_sibl_child->color_;
  auto right_child_color =
      is_right_child_null ? Color::Undefined : right_sibl_child->color_;

  bool accepted = !is_left_child_null && !is_right_child_null &&
                  left_child_color == Color::Black &&
                  right_child_color == Color::Black;

  accepted |= is_left_child_null && !is_right_child_null &&
              right_child_color == Color::Black;

  accepted |= !is_left_child_null && is_right_child_null &&
              left_child_color == Color::Black;

  if (accepted) {
    return BlackSiblingBlackNephew(rb_node, rb_sibling);
  } else {
    return BlackSiblingRedNephew(rb_node, rb_sibling);
  }

  return nullptr;
}

template <typename T, typename M>
Node<T, M> *RedBlackTree<T, M>::BlackSiblingBlackNephew(RBNode<T, M> *node,
                                                        RBNode<T, M> *sibling) {
  this->CheckNode(node, __func__, "node");
  auto *rb_node = GetRBNode(node);
  auto parent = GetRBNode(node->parent_);
  auto rb_sibling = GetRBNode(sibling);
  recolor(rb_sibling);
  if (parent->color_ == Color::Black) {
    delete node;
    recolor(rb_sibling);
    return DoubleBlackCase(parent);
  } else if (parent->color_ == Color::Red) {
    recolor(rb_sibling);
    return node;
  } else {
    this->ErrorMessage("Error in BlackSiblingBlackNephew()");
  }

  return nullptr;
}

///@brief for remove() method
template <typename T, typename M>
Node<T, M> *RedBlackTree<T, M>::BlackSiblingRedNephew(RBNode<T, M> *node,
                                                      RBNode<T, M> *sibling) {

  bool is_right_sibling = !this->IsLeftSideOfNode(sibling);

  auto *left_child = GetRBNode(sibling->left_);
  auto *right_child = GetRBNode(sibling->right_);

  bool left_child_red = IsRedNode(left_child);
  bool right_child_red = IsRedNode(right_child);

  bool accepted = left_child_red || right_child_red;

  if (!accepted) {
    this->ErrorMessage("Error in BlackSiblingRedNephew(): should be at least "
                       "one red newphew ");
  }

  if (is_right_sibling && right_child_red) {
    LeftRotation(node->parent_);
    recolor(right_child);
  } else if (is_right_sibling && !right_child_red) {
    RightRotation(left_child);
    LeftRotation(node->parent_);
    recolor(left_child);
  } else if (!is_right_sibling && right_child_red) {
    LeftRotation(sibling);
    RightRotation(right_child);
    recolor(right_child);
  } else {
    RightRotation(sibling);
    recolor(left_child);
  }

  return node;
}

template <typename T, typename M>
bool RedBlackTree<T, M>::IsRedNode(Node<T, M> *node) const {

  if (node == nullptr) {
    return false;
  }

  auto *rb_node = GetRBNode(node);
  auto color = rb_node->color_;
  if (color == Color::Undefined) {
    this->ErrorMessage("Undefined color");
  }
  return (color == Color::Red);
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
