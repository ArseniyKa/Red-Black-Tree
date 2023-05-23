#include "RedBlackTree.h"

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

///@brief for remove() method
template <typename T, typename M>
Node<T, M> *RedBlackTree<T, M>::BlackSiblingRedNephew(RBNode<T, M> *node,
                                                      RBNode<T, M> *sibling) {

  bool is_right_sibling = !this->IsLeftSideOfNode(sibling);

  bool is_left_child_null = sibling->left_ == nullptr;
  bool is_right_child_null = sibling->right_ == nullptr;

  auto *left_child = is_left_child_null ? nullptr : GetRBNode(sibling->left_);
  auto *right_child =
      is_right_child_null ? nullptr : GetRBNode(sibling->right_);

  bool left_child_red = IsRedNode(left_child);
  bool right_child_red = IsRedNode(right_child);

  bool accepted = left_child_red || right_child_red;

  if (!accepted) {
    this->ErrorMessage("Error in BlackSiblingRedNephew(): should be at least "
                       "one red newphew ");
  }

  auto *rb_parent = GetRBNode(node->parent_);
  if (is_right_sibling && right_child_red) { // right-right case
    LeftRotation(node->parent_);
    recolor(right_child);
    if (rb_parent->color_ == Color::Red) {
      recolor(rb_parent);
      recolor(sibling);
    }
  } else if (is_right_sibling && !right_child_red) {
    RightRotation(left_child);
    LeftRotation(node->parent_);
    if (rb_parent->color_ == Color::Red) {
      recolor(rb_parent);
    } else {
      recolor(left_child);
    }
    ///@todo this is crutch. figure out how is was this problem with parent
    rb_parent->left_ = nullptr;
  } else if (!is_right_sibling && right_child_red) {
    LeftRotation(sibling);
    RightRotation(right_child);
    if (rb_parent->color_ == Color::Red) {
      recolor(rb_parent);
    } else {
      recolor(right_child);
    }
    ///@todo this is crutch. figure out how is was this problem with parent
    rb_parent->right_ = nullptr;
  } else { // left-left case
    RightRotation(sibling);
    recolor(left_child);
    ///@todo this is crutch. figure out how is was this problem with parent
    rb_parent->right_ = nullptr;
  }

  return node;
}

template <typename T, typename M>
Node<T, M> *RedBlackTree<T, M>::BlackSiblingCase(Node<T, M> *node,
                                                 Node<T, M> *sibling) {
  auto *rb_node = GetRBNode(node);
  auto *rb_sibling = GetRBNode(sibling);
  auto sibling_color = rb_sibling->color_;
  bool is_left_child_null = rb_sibling->left_ == nullptr;
  bool is_right_child_null = rb_sibling->right_ == nullptr;

  auto *left_sibl_child =
      is_left_child_null ? nullptr : GetRBNode(rb_sibling->left_);
  auto *right_sibl_child =
      is_right_child_null ? nullptr : GetRBNode(rb_sibling->right_);

  auto left_child_color =
      is_left_child_null ? Color::Undefined : left_sibl_child->color_;
  auto right_child_color =
      is_right_child_null ? Color::Undefined : right_sibl_child->color_;

  bool black_black_case = !is_left_child_null && !is_right_child_null &&
                          left_child_color == Color::Black &&
                          right_child_color == Color::Black;

  black_black_case |= is_left_child_null && !is_right_child_null &&
                      right_child_color == Color::Black;

  black_black_case |= !is_left_child_null && is_right_child_null &&
                      left_child_color == Color::Black;

  black_black_case |= is_left_child_null && is_right_child_null;

  if (black_black_case) {
    return BlackSiblingBlackNephews(rb_node, rb_sibling);
  } else {
    return BlackSiblingRedNephew(rb_node, rb_sibling);
  }

  return nullptr;
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

  BlackSiblingCase(GetRBNode(node), GetRBNode(new_sibling));
  return node;
}

template <typename T, typename M>
Node<T, M> *
RedBlackTree<T, M>::BlackSiblingBlackNephews(RBNode<T, M> *node,
                                             RBNode<T, M> *sibling) {
  this->CheckNode(node, __func__, "node");
  auto *rb_node = GetRBNode(node);
  auto parent = GetRBNode(node->parent_);
  auto rb_sibling = GetRBNode(sibling);
  recolor(rb_sibling);

  ///@note maybe in this pointer nullptr is null
  bool is_left_node = this->IsLeftSideOfNode(node);
  is_left_node ? parent->left_ = nullptr : parent->right_ = nullptr;

  if (parent->color_ == Color::Black) {
    DoubleBlackCase(parent);
    return node;
  } else if (parent->color_ == Color::Red) {
    recolor(parent);
    return node;
  } else {
    this->ErrorMessage("Error in BlackSiblingBlackNephew()");
  }

  return nullptr;
}

// explicit instantiation
template class RedBlackTree<int, std::string>;
template class RedBlackTree<int, int>;
