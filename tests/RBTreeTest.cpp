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

  void checkTreeNodes(RedBlackTree<int, std::string> &tree,
                      std::vector<std::pair<int, Color>> &answers) {

    int index = 0;
    for (auto elem : tree) {
      auto key = elem.first;
      auto *node = tree.find(key);
      auto *rb_node = dynamic_cast<RBNode<int, std::string> *>(node);
      auto color = rb_node->color_;

      EXPECT_EQ(key, answers[index].first);
      EXPECT_EQ(color, answers[index].second);
      index++;
    }
  }
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
// TEST_F(RedBlackTreeTest, LeftRotationTest) { // NOLINT
//  RedBlackTree<int, std::string> tree;

//  tree.BinaryTree::insert(33, "root");
//  tree.BinaryTree::insert(13, "left_sub_root");
//  tree.BinaryTree::insert(20, "right_sub_root");
//  tree.BinaryTree::insert(37, "parent");
//  tree.BinaryTree::insert(50, "X");
//  tree.BinaryTree::insert(47, "alpha");
//  tree.BinaryTree::insert(45, "alpha2");
//  tree.BinaryTree::insert(43, "alpha3");
//  tree.BinaryTree::insert(89, "Y");
//  tree.BinaryTree::insert(92, "gamma");
//  tree.BinaryTree::insert(99, "gamma2");
//  tree.BinaryTree::insert(84, "beta");
//  tree.BinaryTree::insert(82, "beta2");

//  auto *node = tree.find(50);
//  //  std::cout << "node is " << node->value_ << "\n";
//  //  std::cout << "left child is " << node->left_->value_ << "\n";
//  //  std::cout << "right child is " << node->right_->value_ << "\n";

//  //  std::cout << "left child of right child is " <<
//  //  node->right_->left_->value_
//  //            << "\n";
//  //  std::cout << "right child of right child is " <<
//  //  node->right_->right_->value_
//  //            << "\n";

//  //  std::cout << "X parent is " << node->parent_->value_ << "\n";
//  //  std::cout << "parent right child is " << node->parent_->right_->value_
//  //            << "\n";

//  // values
//  auto X_val = node->value_;
//  auto alpha_val = node->left_->value_;
//  auto Y_val = node->right_->value_;
//  auto beta_val = node->right_->left_->value_;
//  auto gamma_val = node->right_->right_->value_;
//  auto parent_val = node->parent_->value_;
//  auto parent_right_child_val = node->parent_->right_->value_;

//  auto size = tree.size();

//  tree.LeftRotation(node);

//  //  std::cout << "===========  LeftRotation()  ==========\n";
//  //  std::cout << "node is " << node->value_ << "\n";
//  //  std::cout << "left child is " << node->left_->value_ << "\n";
//  //  std::cout << "right child is " << node->right_->value_ << "\n";

//  //  std::cout << "parent is " << node->parent_->value_ << "\n";
//  //  std::cout << "sibling is " << node->parent_->right_->value_ << "\n";

//  //  std::cout << "Y parent is " << node->parent_->parent_->value_ << "\n";
//  //  std::cout << "parent child is " <<
//  node->parent_->parent_->right_->value_
//  //            << "\n";

//  // check previouse and next values after rotation.
//  EXPECT_EQ(X_val, node->value_);
//  EXPECT_EQ(alpha_val, node->left_->value_);
//  EXPECT_EQ(Y_val, node->parent_->value_);
//  EXPECT_EQ(beta_val, node->right_->value_);
//  EXPECT_EQ(gamma_val, node->parent_->right_->value_);
//  EXPECT_EQ(parent_val, node->parent_->parent_->value_);
//  EXPECT_EQ(parent_right_child_val, node->value_);

//  EXPECT_EQ(size, tree.size());
//}

////======================================
/////@brief after left rotation:
////                    Y
////          X        ///   gama
////   alpha // beta

/////@brief before left rotation:
////                 X
////       alpha             Y
////                   beta /// gama
////======================================
// TEST_F(RedBlackTreeTest, RightRotationTest) { // NOLINTleft_
//   RedBlackTree<int, std::string> tree;

//  tree.BinaryTree::insert(33, "root");
//  tree.BinaryTree::insert(13, "left_sub_root");
//  tree.BinaryTree::insert(20, "right_sub_root");
//  tree.BinaryTree::insert(37, "parent");
//  tree.BinaryTree::insert(89, "Y");
//  tree.BinaryTree::insert(50, "X");
//  tree.BinaryTree::insert(47, "alpha");
//  tree.BinaryTree::insert(45, "alpha2");
//  tree.BinaryTree::insert(43, "alpha3");
//  tree.BinaryTree::insert(84, "beta");
//  tree.BinaryTree::insert(82, "beta2");
//  tree.BinaryTree::insert(92, "gamma");
//  tree.BinaryTree::insert(99, "gamma2");

//  auto *node = tree.find(50);
//  //  std::cout << "node is " << node->value_ << "\n";
//  //  std::cout << "left child is " << node->left_->value_ << "\n";
//  //  std::cout << "right child is " << node->right_->value_ << "\n";

//  //  std::cout << "X parent is " << node->parent_->value_ << "\n";
//  //  std::cout << "X sibling is " << node->parent_->right_->value_ << "\n";
//  //  std::cout << "Y parent is " << node->parent_->parent_->value_ << "\n";
//  //  std::cout << "Y parent right child is "
//  //            << node->parent_->parent_->right_->value_ << "\n";

//  auto X_val = node->value_;
//  auto alpha_val = node->left_->value_;
//  auto beta_val = node->right_->value_;
//  auto Y_val = node->parent_->value_;
//  auto upper_parent = node->parent_->parent_->value_;
//  auto upper_parent_right_child_val = node->parent_->parent_->right_->value_;
//  auto gamma = node->parent_->right_->value_;

//  auto size = tree.size();

//  tree.RightRotation(node);

//  //  std::cout << "===========  RightRotation()  ==========\n";
//  //  std::cout << "node is " << node->value_ << "\n";
//  //  std::cout << "left child is " << node->left_->value_ << "\n";
//  //  std::cout << "right child is " << node->right_->value_ << "\n";

//  //  std::cout << "X parent is " << node->parent_->value_ << "\n";
//  //  std::cout << "Y parent is " << node->right_->parent_->value_ << "\n";

//  //  std::cout << "parent right child is " << node->parent_->right_->value_
//  //            << "\n";

//  //  std::cout << "left child of right child is " <<
//  //  node->right_->left_->value_
//  //            << "\n";
//  //  std::cout << "right child of right child is " <<
//  //  node->right_->right_->value_
//  //            << "\n";

//  // check previous and next values after rotation.
//  EXPECT_EQ(X_val, node->value_);
//  EXPECT_EQ(alpha_val, node->left_->value_);
//  EXPECT_EQ(beta_val, node->right_->left_->value_);
//  EXPECT_EQ(gamma, node->right_->right_->value_);
//  EXPECT_EQ(Y_val, node->right_->value_);
//  EXPECT_EQ(upper_parent, node->parent_->value_);
//  EXPECT_EQ(upper_parent_right_child_val, node->right_->value_);

//  EXPECT_EQ(size, tree.size());
//}

// TEST_F(RedBlackTreeTest, GetNodeUncleTest) { // NOLINTleft_
//   RedBlackTree<int, std::string> tree;

//  tree.BinaryTree::insert(33, "root");
//  tree.BinaryTree::insert(13, "left_sub_root");
//  tree.BinaryTree::insert(10, "left_sub_sub_root");
//  tree.BinaryTree::insert(34, "right_sub_root");
//  tree.BinaryTree::insert(37, "parent");
//  tree.BinaryTree::insert(50, "X");
//  tree.BinaryTree::insert(47, "alpha");
//  tree.BinaryTree::insert(45, "alpha2");
//  tree.BinaryTree::insert(43, "alpha3");
//  tree.BinaryTree::insert(89, "Y");
//  tree.BinaryTree::insert(92, "gamma");
//  tree.BinaryTree::insert(99, "gamma2");
//  tree.BinaryTree::insert(84, "beta");
//  tree.BinaryTree::insert(82, "beta2");

//  auto *node1 = tree.find(50);
//  auto *uncle1 = tree.GetUncle(node1);
//  EXPECT_EQ(uncle1, nullptr);

//  auto node2 = tree.find(92);
//  auto *uncle2 = tree.GetUncle(node2);
//  EXPECT_EQ(uncle2->value_, "alpha");

//  auto node3 = tree.find(10);
//  auto *uncle3 = tree.GetUncle(node3);
//  EXPECT_EQ(uncle3->value_, "right_sub_root");
//  qDebug() << uncle3->value_.data();

//  //  bool is_exception = false;
//  std::string error_message;
//  try {

//    auto node4 = tree.find(13);
//    auto *uncle4 = tree.GetUncle(node4);
//  } catch (std::exception &ex) {
//    error_message = ex.what();
//  }

//  EXPECT_EQ(error_message, "Error in GetUncle(): grandfather is nullptr");
//}

// TEST_F(RedBlackTreeTest, IsLeftSideOfNodeTest) { // NOLINTleft_
//   RedBlackTree<int, std::string> tree;

//  tree.BinaryTree::insert(33, "root");
//  tree.BinaryTree::insert(13, "left_sub_root");
//  tree.BinaryTree::insert(10, "left_sub_sub_root");
//  tree.BinaryTree::insert(34, "right_sub_root");
//  tree.BinaryTree::insert(37, "parent");
//  tree.BinaryTree::insert(50, "X");
//  tree.BinaryTree::insert(47, "alpha");
//  tree.BinaryTree::insert(45, "alpha2");
//  tree.BinaryTree::insert(43, "alpha3");
//  tree.BinaryTree::insert(89, "Y");
//  tree.BinaryTree::insert(92, "gamma");
//  tree.BinaryTree::insert(99, "gamma2");
//  tree.BinaryTree::insert(84, "beta");
//  tree.BinaryTree::insert(82, "beta2");

//  auto *node1 = tree.find(50);
//  bool is_left_node1 = tree.IsLeftSideOfNode(node1);
//  EXPECT_EQ(is_left_node1, false);

//  auto *node2 = tree.find(13);
//  bool is_left_node2 = tree.IsLeftSideOfNode(node2);
//  EXPECT_EQ(is_left_node2, true);

//  auto *node3 = tree.find(89);
//  bool is_left_node3 = tree.IsLeftSideOfNode(node3);
//  EXPECT_EQ(is_left_node3, false);

//  auto *node4 = tree.find(82);
//  bool is_left_node4 = tree.IsLeftSideOfNode(node4);
//  EXPECT_EQ(is_left_node4, true);
//}

// see the link:https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
TEST_F(RedBlackTreeTest, insert_RedParentRedUncle_Test) { // NOLINTleft_
  RedBlackTree<int, std::string> tree;

  tree.insert(61, "root");
  tree.insert(52, "left_sub_root");
  tree.insert(85, "right_sub_root");
  tree.insert(76, "uncle");
  tree.insert(93, "parent");

  // insert new node
  tree.insert(100, "X");

  std::vector<std::pair<int, Color>> answers{
      {52, Color::Black}, {61, Color::Black}, {76, Color::Black},
      {85, Color::Red},   {93, Color::Black}, {100, Color::Red}};

  checkTreeNodes(tree, answers);
}

// see the link:https://algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
TEST_F(RedBlackTreeTest, insert_RightParentRightNodeCase_Test) { // NOLINTleft_
  RedBlackTree<int, std::string> tree;

  tree.insert(61, "root");
  tree.insert(52, "left_sub_root");
  tree.insert(85, "right_sub_root");
  tree.insert(93, "parent");

  // insert new node
  tree.insert(100, "X");

  std::vector<std::pair<int, Color>> answers{{52, Color::Black},
                                             {61, Color::Black},
                                             {85, Color::Red},
                                             {93, Color::Black},
                                             {100, Color::Red}};

  checkTreeNodes(tree, answers);
}

} // namespace bstree::test
