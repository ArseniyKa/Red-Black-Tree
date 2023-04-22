#include <gtest/gtest.h>

#include "RedBlackTree.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace bstree::test {

class RedBlackTreeTest : public testing::Test {
protected:
  RedBlackTreeTest() = default;
};

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
TEST_F(RedBlackTreeTest, LeftRotationTest) { // NOLINT
  RedBlackTree<int, std::string> tree;

  tree.BinaryTree::insert(33, "root");
  tree.BinaryTree::insert(13, "left_sub_root");
  tree.BinaryTree::insert(20, "right_sub_root");
  tree.BinaryTree::insert(37, "parent");
  tree.BinaryTree::insert(50, "X");
  tree.BinaryTree::insert(47, "alpha");
  tree.BinaryTree::insert(45, "alpha2");
  tree.BinaryTree::insert(43, "alpha3");
  tree.BinaryTree::insert(89, "Y");
  tree.BinaryTree::insert(92, "gamma");
  tree.BinaryTree::insert(99, "gamma2");
  tree.BinaryTree::insert(84, "beta");
  tree.BinaryTree::insert(82, "beta2");

  auto *node = tree.find(50);
  std::cout << "node is " << node->value_ << "\n";
  std::cout << "left child is " << node->left_->value_ << "\n";
  std::cout << "right child is " << node->right_->value_ << "\n";

  std::cout << "left child of right child is " << node->right_->left_->value_
            << "\n";
  std::cout << "right child of right child is " << node->right_->right_->value_
            << "\n";

  std::cout << "X parent is " << node->parent_->value_ << "\n";
  std::cout << "parent child is " << node->parent_->right_->value_ << "\n";

  auto node_val = node->value_;
  auto left_child_val = node->left_->value_;
  auto right_child_val = node->right_->value_;
  auto left_child_of_right_child_val = node->right_->left_->value_;
  auto right_child_of_right_child_val = node->right_->right_->value_;
  auto X_parent_val = node->parent_->value_;
  auto parent_child_val = node->parent_->right_->value_;

  auto size = tree.size();

  tree.LeftRotation(node);

  std::cout << "=====================\n";
  std::cout << "node is " << node->value_ << "\n";
  std::cout << "left child is " << node->left_->value_ << "\n";
  std::cout << "right child is " << node->right_->value_ << "\n";

  std::cout << "parent is " << node->parent_->value_ << "\n";
  std::cout << "sibling is " << node->parent_->right_->value_ << "\n";

  std::cout << "Y parent is " << node->parent_->parent_->value_ << "\n";
  std::cout << "parent child is " << node->parent_->parent_->right_->value_
            << "\n";

  // check previouse and next values after rotation.
  EXPECT_EQ(node_val, node->value_);
  EXPECT_EQ(left_child_val, node->left_->value_);
  EXPECT_EQ(right_child_val, node->parent_->value_);
  EXPECT_EQ(left_child_of_right_child_val, node->right_->value_);
  EXPECT_EQ(right_child_of_right_child_val, node->parent_->right_->value_);
  EXPECT_EQ(X_parent_val, node->parent_->parent_->value_);
  EXPECT_EQ(parent_child_val, node->value_);

  EXPECT_EQ(size, tree.size());
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
TEST_F(RedBlackTreeTest, RightRotationTest) { // NOLINTleft_
  RedBlackTree<int, std::string> tree;

  tree.BinaryTree::insert(33, "root");
  tree.BinaryTree::insert(13, "left_sub_root");
  tree.BinaryTree::insert(20, "right_sub_root");
  tree.BinaryTree::insert(37, "parent");
  tree.BinaryTree::insert(50, "X");
  tree.BinaryTree::insert(47, "alpha");
  tree.BinaryTree::insert(45, "alpha2");
  tree.BinaryTree::insert(43, "alpha3");
  tree.BinaryTree::insert(89, "Y");
  tree.BinaryTree::insert(92, "gamma");
  tree.BinaryTree::insert(99, "gamma2");
  tree.BinaryTree::insert(84, "beta");
  tree.BinaryTree::insert(82, "beta2");

  auto *node = tree.find(50);
  std::cout << "node is " << node->value_ << "\n";
  std::cout << "left child is " << node->left_->value_ << "\n";
  std::cout << "right child is " << node->right_->value_ << "\n";

  std::cout << "left child of right child is " << node->right_->left_->value_
            << "\n";
  std::cout << "right child of right child is " << node->right_->right_->value_
            << "\n";

  std::cout << "X parent is " << node->parent_->value_ << "\n";
  std::cout << "parent child is " << node->parent_->right_->value_ << "\n";

  auto node_val = node->value_;
  auto left_child_val = node->left_->value_;
  auto right_child_val = node->right_->value_;
  auto left_child_of_right_child_val = node->right_->left_->value_;
  auto right_child_of_right_child_val = node->right_->right_->value_;
  auto X_parent_val = node->parent_->value_;
  auto parent_child_val = node->parent_->right_->value_;

  auto size = tree.size();

  tree.LeftRotation(node);

  std::cout << "=====================\n";
  std::cout << "node is " << node->value_ << "\n";
  std::cout << "left child is " << node->left_->value_ << "\n";
  std::cout << "right child is " << node->right_->value_ << "\n";

  std::cout << "parent is " << node->parent_->value_ << "\n";
  std::cout << "sibling is " << node->parent_->right_->value_ << "\n";

  std::cout << "Y parent is " << node->parent_->parent_->value_ << "\n";
  std::cout << "parent child is " << node->parent_->parent_->right_->value_
            << "\n";

  // check previouse and next values after rotation.
  EXPECT_EQ(node_val, node->value_);
  EXPECT_EQ(left_child_val, node->left_->value_);
  EXPECT_EQ(right_child_val, node->parent_->value_);
  EXPECT_EQ(left_child_of_right_child_val, node->right_->value_);
  EXPECT_EQ(right_child_of_right_child_val, node->parent_->right_->value_);
  EXPECT_EQ(X_parent_val, node->parent_->parent_->value_);
  EXPECT_EQ(parent_child_val, node->value_);

  EXPECT_EQ(size, tree.size());
}
} // namespace bstree::test
