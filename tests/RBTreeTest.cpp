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

  template <typename T, typename M>
  void checkTreeNodes(RedBlackTree<T, M> &tree,
                      std::vector<std::pair<T, Color>> &answers) {

    int index = 0;
    for (auto elem : tree) {
      auto key = elem.first;
      auto *node = tree.find(key);
      auto *rb_node = dynamic_cast<RBNode<T, M> *>(node);
      auto color = rb_node->color_;

      EXPECT_EQ(key, answers[index].first);
      EXPECT_EQ(color, answers[index].second);
      index++;
    }
  }

  template <typename T, typename M>
  void checkNode(RBNode<T, M> *node, T true_key, Color true_color) {
    EXPECT_EQ(node->key_, true_key);
    EXPECT_EQ(node->color_, true_color);
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
  //  std::cout << "node is " << node->value_ << "\n";
  //  std::cout << "left child is " << node->left_->value_ << "\n";
  //  std::cout << "right child is " << node->right_->value_ << "\n";

  //  std::cout << "left child of right child is " <<
  //  node->right_->left_->value_
  //            << "\n";
  //  std::cout << "right child of right child is " <<
  //  node->right_->right_->value_
  //            << "\n";

  //  std::cout << "X parent is " << node->parent_->value_ << "\n";
  //  std::cout << "parent right child is " << node->parent_->right_->value_
  //            << "\n";

  // values
  auto X_val = node->value_;
  auto alpha_val = node->left_->value_;
  auto Y_val = node->right_->value_;
  auto beta_val = node->right_->left_->value_;
  auto gamma_val = node->right_->right_->value_;
  auto parent_val = node->parent_->value_;
  auto parent_right_child_val = node->parent_->right_->value_;

  auto size = tree.size();

  tree.LeftRotation(node);

  //  std::cout << "===========  LeftRotation()  ==========\n";
  //  std::cout << "node is " << node->value_ << "\n";
  //  std::cout << "left child is " << node->left_->value_ << "\n";
  //  std::cout << "right child is " << node->right_->value_ << "\n";

  //  std::cout << "parent is " << node->parent_->value_ << "\n";
  //  std::cout << "sibling is " << node->parent_->right_->value_ << "\n";

  //  std::cout << "Y parent is " << node->parent_->parent_->value_ << "\n";
  //  std::cout << "parent child is " <<
  //    node->parent_->parent_->right_->value_
  //            << "\n";

  // check previouse and next values after rotation.
  EXPECT_EQ(X_val, node->value_);
  EXPECT_EQ(alpha_val, node->left_->value_);
  EXPECT_EQ(Y_val, node->parent_->value_);
  EXPECT_EQ(beta_val, node->right_->value_);
  EXPECT_EQ(gamma_val, node->parent_->right_->value_);
  EXPECT_EQ(parent_val, node->parent_->parent_->value_);
  EXPECT_EQ(parent_right_child_val, node->value_);

  EXPECT_EQ(size, tree.size());
}

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
TEST_F(RedBlackTreeTest, RightRotationTest) { // NOLINTleft_
  RedBlackTree<int, std::string> tree;

  tree.BinaryTree::insert(33, "root");
  tree.BinaryTree::insert(13, "left_sub_root");
  tree.BinaryTree::insert(20, "right_sub_root");
  tree.BinaryTree::insert(37, "parent");
  tree.BinaryTree::insert(89, "Y");
  tree.BinaryTree::insert(50, "X");
  tree.BinaryTree::insert(47, "alpha");
  tree.BinaryTree::insert(45, "alpha2");
  tree.BinaryTree::insert(43, "alpha3");
  tree.BinaryTree::insert(84, "beta");
  tree.BinaryTree::insert(82, "beta2");
  tree.BinaryTree::insert(92, "gamma");
  tree.BinaryTree::insert(99, "gamma2");

  auto *node = tree.find(50);
  //  std::cout << "node is " << node->value_ << "\n";
  //  std::cout << "left child is " << node->left_->value_ << "\n";
  //  std::cout << "right child is " << node->right_->value_ << "\n";

  //  std::cout << "X parent is " << node->parent_->value_ << "\n";
  //  std::cout << "X sibling is " << node->parent_->right_->value_ << "\n";
  //  std::cout << "Y parent is " << node->parent_->parent_->value_ << "\n";
  //  std::cout << "Y parent right child is "
  //            << node->parent_->parent_->right_->value_ << "\n";

  auto X_val = node->value_;
  auto alpha_val = node->left_->value_;
  auto beta_val = node->right_->value_;
  auto Y_val = node->parent_->value_;
  auto upper_parent = node->parent_->parent_->value_;
  auto upper_parent_right_child_val = node->parent_->parent_->right_->value_;
  auto gamma = node->parent_->right_->value_;

  auto size = tree.size();

  tree.RightRotation(node);

  //  std::cout << "===========  RightRotation()  ==========\n";
  //  std::cout << "node is " << node->value_ << "\n";
  //  std::cout << "left child is " << node->left_->value_ << "\n";
  //  std::cout << "right child is " << node->right_->value_ << "\n";

  //  std::cout << "X parent is " << node->parent_->value_ << "\n";
  //  std::cout << "Y parent is " << node->right_->parent_->value_ << "\n";

  //  std::cout << "parent right child is " << node->parent_->right_->value_
  //            << "\n";

  //  std::cout << "left child of right child is " <<
  //  node->right_->left_->value_
  //            << "\n";
  //  std::cout << "right child of right child is " <<
  //  node->right_->right_->value_
  //            << "\n";

  // check previous and next values after rotation.
  EXPECT_EQ(X_val, node->value_);
  EXPECT_EQ(alpha_val, node->left_->value_);
  EXPECT_EQ(beta_val, node->right_->left_->value_);
  EXPECT_EQ(gamma, node->right_->right_->value_);
  EXPECT_EQ(Y_val, node->right_->value_);
  EXPECT_EQ(upper_parent, node->parent_->value_);
  EXPECT_EQ(upper_parent_right_child_val, node->right_->value_);

  EXPECT_EQ(size, tree.size());
}

TEST_F(RedBlackTreeTest, GetNodeUncleTest) { // NOLINTleft_
  RedBlackTree<int, std::string> tree;

  tree.BinaryTree::insert(33, "root");
  tree.BinaryTree::insert(13, "left_sub_root");
  tree.BinaryTree::insert(10, "left_sub_sub_root");
  tree.BinaryTree::insert(34, "right_sub_root");
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

  auto *node1 = tree.find(50);
  auto *uncle1 = tree.GetUncle(node1);
  EXPECT_EQ(uncle1, nullptr);

  auto node2 = tree.find(92);
  auto *uncle2 = tree.GetUncle(node2);
  EXPECT_EQ(uncle2->value_, "alpha");

  auto node3 = tree.find(10);
  auto *uncle3 = tree.GetUncle(node3);
  EXPECT_EQ(uncle3->value_, "right_sub_root");
  qDebug() << uncle3->value_.data();

  //  bool is_exception = false;
  std::string error_message;
  try {

    auto node4 = tree.find(13);
    auto *uncle4 = tree.GetUncle(node4);
  } catch (std::exception &ex) {
    error_message = ex.what();
  }

  EXPECT_EQ(error_message, "Error in GetUncle(): grandfather is nullptr");
}

TEST_F(RedBlackTreeTest, IsLeftSideOfNodeTest) { // NOLINTleft_
  RedBlackTree<int, std::string> tree;

  tree.BinaryTree::insert(33, "root");
  tree.BinaryTree::insert(13, "left_sub_root");
  tree.BinaryTree::insert(10, "left_sub_sub_root");
  tree.BinaryTree::insert(34, "right_sub_root");
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

  auto *node1 = tree.find(50);
  bool is_left_node1 = tree.IsLeftSideOfNode(node1);
  EXPECT_EQ(is_left_node1, false);

  auto *node2 = tree.find(13);
  bool is_left_node2 = tree.IsLeftSideOfNode(node2);
  EXPECT_EQ(is_left_node2, true);

  auto *node3 = tree.find(89);
  bool is_left_node3 = tree.IsLeftSideOfNode(node3);
  EXPECT_EQ(is_left_node3, false);

  auto *node4 = tree.find(82);
  bool is_left_node4 = tree.IsLeftSideOfNode(node4);
  EXPECT_EQ(is_left_node4, true);
}

// see the link : https: //
// algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
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

// see the link : https
//    : // algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
TEST_F(RedBlackTreeTest, insert_RightParentRightNodeCase_Test) {
  RedBlackTree<int, std::string> tree;

  tree.insert(61, "root");
  tree.insert(52, "left_sub_root");
  tree.insert(85, "right_sub_root");
  tree.insert(93, "parent");

  ///@todo resolve the problem with iterator, the last elemend is 888 and
  //  after
  /// for loop insert() leads to an error
  //  std::vector<std::pair<int, Color>> answers{{52, Color::Black},
  //                                             {61, Color::Black},
  //                                             {85, Color::Black},
  //                                             {93, Color::Red}};

  //  checkTreeNodes(tree, answers);

  // insert new node
  tree.insert(100, "X");

  std::vector<std::pair<int, Color>> answers = {{52, Color::Black},
                                                {61, Color::Black},
                                                {85, Color::Red},
                                                {93, Color::Black},
                                                {100, Color::Red}};

  checkTreeNodes(tree, answers);
}

// see the link : https: //
// algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
TEST_F(RedBlackTreeTest, insert_RightParentLeftNodeCase_Test) {
  RedBlackTree<int, std::string> tree;

  tree.insert(61, "root");
  tree.insert(52, "left_sub_root");
  tree.insert(85, "right_sub_root");
  tree.insert(93, "parent");

  //  std::vector<std::pair<int, Color>> answers{{52, Color::Black},
  //                                             {61, Color::Black},
  //                                             {85, Color::Black},
  //                                             {93, Color::Red}};
  //  checkTreeNodes(tree, answers);

  // insert new node
  tree.insert(87, "X");

  std::vector<std::pair<int, Color>> answers = {{52, Color::Black},
                                                {61, Color::Black},
                                                {85, Color::Red},
                                                {87, Color::Black},
                                                {93, Color::Red}};

  checkTreeNodes(tree, answers);
}

// see the link : https: //
// algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
TEST_F(RedBlackTreeTest,
       insert_LeftParentLeftNodeCaseCase_Test) { // NOLINTleft_
  RedBlackTree<int, std::string> tree;

  tree.insert(61, "root");
  tree.insert(52, "left_sub_root");
  tree.insert(85, "right_sub_root");
  tree.insert(81, "parent");

  // insert new node
  tree.insert(75, "X");

  std::vector<std::pair<int, Color>> answers = {{52, Color::Black},
                                                {61, Color::Black},
                                                {75, Color::Red},
                                                {81, Color::Black},
                                                {85, Color::Red}};

  checkTreeNodes(tree, answers);
}

// see the
// link : https : // algorithmtutor.com/Data-Structures/Tree/Red-Black-Trees/
TEST_F(RedBlackTreeTest, insert_LeftParentRightNodeCase_Test) {
  RedBlackTree<int, std::string> tree;

  tree.insert(61, "root");
  tree.insert(52, "left_sub_root");
  tree.insert(85, "right_sub_root");
  tree.insert(75, "parent");

  // insert new node
  tree.insert(79, "X");

  std::vector<std::pair<int, Color>> answers = {{52, Color::Black},
                                                {61, Color::Black},
                                                {75, Color::Red},
                                                {79, Color::Black},
                                                {85, Color::Red}};

  checkTreeNodes(tree, answers);
}

TEST_F(RedBlackTreeTest,
       insert_Linear_Subsequence_Test) { // NOLINTleft_
  RedBlackTree<int, int> tree;

  for (int i = 0; i < 10; i++) {
    tree.insert(i, i);
  }

  std::vector<std::pair<int, Color>> answers = {
      {0, Color::Black}, {1, Color::Black}, {2, Color::Black},
      {3, Color::Black}, {4, Color::Black}, {5, Color::Black},
      {6, Color::Black}, {7, Color::Red},   {8, Color::Black},
      {9, Color::Red}};

  checkTreeNodes(tree, answers);

  auto *root = tree.root();
  auto *rb_root = tree.GetRBNode(root);

  // clang-format off
  //                         3
  //                1                5
  //             0    2          4        7
  //                                   6    8
  //                                          9
  // clang-format on
  checkNode(rb_root, 3, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_), 1, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_->left_), 0, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_->right_), 2, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_), 5, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->left_), 4, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->right_), 7, Color::Red);
  checkNode(tree.GetRBNode(rb_root->right_->right_->left_), 6, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->right_->right_), 8, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->right_->right_->right_), 9,
            Color::Red);

  EXPECT_EQ(tree.size(), 10);
}

TEST_F(RedBlackTreeTest, CopyConstructorTest) { // NOLINT

  RedBlackTree<int, int> old_tree;

  for (int i = 0; i < 10; i++) {
    old_tree.insert(i, i);
  }

  auto new_tree1 = old_tree;
  RedBlackTree<int, int> new_tree2(old_tree);
  EXPECT_EQ(new_tree1.size(), old_tree.size());
  EXPECT_EQ(new_tree2.size(), old_tree.size());

  auto old_itr = old_tree.begin();
  auto new_itr1 = new_tree1.begin();
  auto new_itr2 = new_tree2.begin();
  while (old_itr != old_tree.end() && new_itr1 != new_tree1.end() &&
         new_itr2 != new_tree2.end()) {
    auto old_key = old_itr.node()->key_;
    auto new_key1 = new_itr1.node()->key_;
    auto new_key2 = new_itr2.node()->key_;
    EXPECT_EQ(old_key, new_key1);
    EXPECT_EQ(old_key, new_key2);
    ++old_itr;
    ++new_itr1;
    ++new_itr2;
  }

  auto *root = new_tree1.root();
  auto *rb_root = new_tree1.GetRBNode(root);

  // clang-format off
          //                         3
          //                1                5
          //             0    2          4        7
          //                                   6    8
          //                                          9
  // clang-format on
  checkNode(rb_root, 3, Color::Black);
  checkNode(new_tree1.GetRBNode(rb_root->left_), 1, Color::Black);
  checkNode(new_tree1.GetRBNode(rb_root->left_->left_), 0, Color::Black);
  checkNode(new_tree1.GetRBNode(rb_root->left_->right_), 2, Color::Black);
  checkNode(new_tree1.GetRBNode(rb_root->right_), 5, Color::Black);
  checkNode(new_tree1.GetRBNode(rb_root->right_->left_), 4, Color::Black);
  checkNode(new_tree1.GetRBNode(rb_root->right_->right_), 7, Color::Red);
  checkNode(new_tree1.GetRBNode(rb_root->right_->right_->left_), 6,
            Color::Black);
  checkNode(new_tree1.GetRBNode(rb_root->right_->right_->right_), 8,
            Color::Black);
  checkNode(new_tree1.GetRBNode(rb_root->right_->right_->right_->right_), 9,
            Color::Red);
}

TEST_F(RedBlackTreeTest, MoveConstructorTest) { // NOLINT

  RedBlackTree<int, int> old_tree;

  for (int i = 0; i < 10; i++) {
    old_tree.insert(i, i);
  }

  auto new_tree1 = std::move(old_tree);

  for (int i = 0; i < 10; i++) {
    old_tree.insert(i, i);
  }
  RedBlackTree<int, int> new_tree2(std::move(old_tree));
  EXPECT_EQ(new_tree1.size(), new_tree2.size());
  EXPECT_EQ(old_tree.size(), 0);

  try {
    EXPECT_EQ(old_tree.root(), nullptr);
  } catch (...) {
    EXPECT_EQ(true, true);
  }

  auto new_itr1 = new_tree1.begin();
  auto new_itr2 = new_tree2.begin();
  while (new_itr1 != new_tree1.end() && new_itr2 != new_tree2.end()) {
    auto new_key1 = new_itr1.node()->key_;
    auto new_key2 = new_itr2.node()->key_;
    EXPECT_EQ(new_key1, new_key2);
    ++new_itr1;
    ++new_itr2;
  }

  auto *root = new_tree1.root();
  auto *rb_root = new_tree1.GetRBNode(root);

  // clang-format off
          //                         3
          //                1                5
          //             0    2          4        7
          //                                   6    8
          //                                          9
  // clang-format on
  checkNode(rb_root, 3, Color::Black);
  checkNode(new_tree1.GetRBNode(rb_root->left_), 1, Color::Black);
  checkNode(new_tree1.GetRBNode(rb_root->left_->left_), 0, Color::Black);
  checkNode(new_tree1.GetRBNode(rb_root->left_->right_), 2, Color::Black);
  checkNode(new_tree1.GetRBNode(rb_root->right_), 5, Color::Black);
  checkNode(new_tree1.GetRBNode(rb_root->right_->left_), 4, Color::Black);
  checkNode(new_tree1.GetRBNode(rb_root->right_->right_), 7, Color::Red);
  checkNode(new_tree1.GetRBNode(rb_root->right_->right_->left_), 6,
            Color::Black);
  checkNode(new_tree1.GetRBNode(rb_root->right_->right_->right_), 8,
            Color::Black);
  checkNode(new_tree1.GetRBNode(rb_root->right_->right_->right_->right_), 9,
            Color::Red);
}

} // namespace bstree::test
