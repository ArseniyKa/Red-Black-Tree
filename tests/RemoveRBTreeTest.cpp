#include <gtest/gtest.h>

#include "RedBlackTree.h"
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace bstree::test {

class RemoveRedBlackTreeTest : public testing::Test {
protected:
  RemoveRedBlackTreeTest() = default;

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

  // clang-format off
            //                         3
            //                1                5
            //             0    2          4        7(r)
            //                                   6    8
            //                                          9(r)
  // clang-format on
  template <typename T, typename M>
  void CheckSequencyTree(const RedBlackTree<T, M> &tree) {
    auto *root = tree.root();
    auto *rb_root = tree.GetRBNode(root);

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

  RedBlackTree<int, int> CreateSequancyTree() {
    RedBlackTree<int, int> tree;

    for (int i = 0; i < 10; i++) {
      tree.insert(i, i);
    }

    CheckSequencyTree(tree);
    return tree;
  }
};

TEST_F(RemoveRedBlackTreeTest, remove_AllLeavesEmpty_Red_Deletion_Test) {

  auto tree = CreateSequancyTree();
  tree.remove(9);

  auto *root = tree.root();
  auto *rb_root = tree.GetRBNode(root);

  // clang-format off
            //                         3
            //                1                5
            //             0    2          4        7
            //                                   6    8
            //
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

  EXPECT_EQ(rb_root->right_->right_->right_->right_, nullptr);
  EXPECT_EQ(rb_root->right_->right_->right_->left_, nullptr);
  EXPECT_EQ(tree.size(), 9);
}

TEST_F(RemoveRedBlackTreeTest, remove_AllLeavesEmpty_Black_Deletion_RR_Test) {

  auto tree = CreateSequancyTree();
  tree.remove(6);

  auto *root = tree.root();
  auto *rb_root = tree.GetRBNode(root);

  // clang-format off
            //                         3
            //                1                5
            //             0    2          4        8(r)
            //                                   7     9
            //
  // clang-format on
  checkNode(rb_root, 3, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_), 1, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_->left_), 0, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_->right_), 2, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_), 5, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->left_), 4, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->right_), 8, Color::Red);
  checkNode(tree.GetRBNode(rb_root->right_->right_->left_), 7, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->right_->right_), 9, Color::Black);

  EXPECT_EQ(rb_root->right_->right_->right_->right_, nullptr);
  EXPECT_EQ(rb_root->right_->right_->right_->left_, nullptr);
  EXPECT_EQ(tree.size(), 9);
}

TEST_F(RemoveRedBlackTreeTest, remove_AllLeavesEmpty_Black_Deletion_RL_Test) {

  auto tree = CreateSequancyTree();
  tree.insert(15, 15);
  tree.insert(12, 12);

  auto *root = tree.root();
  auto *rb_root = tree.GetRBNode(root);

  // clang-format off
            //                         3
            //                1                7
            //             0    2          5(r)         9(r)
            //                          4     6      8          15
            //                                              12(r)
            //
  // clang-format on
  checkNode(rb_root, 3, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_), 1, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_->left_), 0, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_->right_), 2, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_), 7, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->left_), 5, Color::Red);
  checkNode(tree.GetRBNode(rb_root->right_->left_->left_), 4, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->left_->right_), 6, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->right_), 9, Color::Red);
  checkNode(tree.GetRBNode(rb_root->right_->right_->left_), 8, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->right_->right_), 15, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->right_->right_->left_), 12,
            Color::Red);

  EXPECT_EQ(tree.size(), 12);

  ///////////////////////////////////////////////

  tree.remove(8);

  // clang-format off
            //                         3
            //                1                   7
            //             0    2          5(r)          12(r)
            //                          4      6       9      15
            //
            //
  // clang-format on
  checkNode(rb_root, 3, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_), 1, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_->left_), 0, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_->right_), 2, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_), 7, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->left_), 5, Color::Red);
  checkNode(tree.GetRBNode(rb_root->right_->left_->left_), 4, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->left_->right_), 6, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->right_), 12, Color::Red);
  checkNode(tree.GetRBNode(rb_root->right_->right_->left_), 9, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->right_->right_), 15, Color::Black);

  // leaves for 15 node
  EXPECT_EQ(rb_root->right_->right_->right_->right_, nullptr);
  EXPECT_EQ(rb_root->right_->right_->right_->left_, nullptr);

  // leaves for 9 node
  EXPECT_EQ(rb_root->right_->right_->left_->left_, nullptr);
  EXPECT_EQ(rb_root->right_->right_->left_->right_, nullptr);

  // leaves for 0 node
  EXPECT_EQ(rb_root->left_->left_->left_, nullptr);
  EXPECT_EQ(rb_root->left_->left_->right_, nullptr);

  // leaves for 2 node
  EXPECT_EQ(rb_root->left_->right_->left_, nullptr);
  EXPECT_EQ(rb_root->left_->right_->right_, nullptr);

  EXPECT_EQ(tree.size(), 11);
}

TEST_F(RemoveRedBlackTreeTest, remove_AllLeavesEmpty_Black_Deletion_LL_Test) {

  auto tree = CreateSequancyTree();
  tree.insert(-1, -1);

  auto *root = tree.root();
  auto *rb_root = tree.GetRBNode(root);

  // clang-format off
            //                         3
            //                1                5
            //             0    2          4        7(r)
            //          -1(r)                      6    8
            //                                          9(r)
  // clang-format on
  checkNode(rb_root, 3, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_), 1, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_->left_), 0, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_->left_->left_), -1, Color::Red);
  checkNode(tree.GetRBNode(rb_root->left_->right_), 2, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_), 5, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->left_), 4, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->right_), 7, Color::Red);
  checkNode(tree.GetRBNode(rb_root->right_->right_->left_), 6, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->right_->right_), 8, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->right_->right_->right_), 9,
            Color::Red);

  EXPECT_EQ(tree.size(), 11);

  ///////////////////////////////////////////////

  tree.remove(2);

  // clang-format off
            //                         3
            //                1                   7
            //             0    2          5(r)          12(r)
            //                          4      6       9      15
            //
            //
  // clang-format on
  checkNode(rb_root, 3, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_), 0, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_->left_), -1, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_->right_), 1, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_), 5, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->left_), 4, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->right_), 7, Color::Red);
  checkNode(tree.GetRBNode(rb_root->right_->right_->left_), 6, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->right_->right_), 8, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->right_->right_->right_), 9,
            Color::Red);

  //  // leaves for -1 node
  EXPECT_EQ(rb_root->left_->left_->left_, nullptr);
  EXPECT_EQ(rb_root->left_->left_->right_, nullptr);

  // leaves for 1 node
  EXPECT_EQ(rb_root->left_->right_->left_, nullptr);
  EXPECT_EQ(rb_root->left_->right_->right_, nullptr);

  EXPECT_EQ(tree.size(), 10);
}

TEST_F(RemoveRedBlackTreeTest, remove_AllLeavesEmpty_Black_Deletion_LR_Test) {

  RedBlackTree<int, int> tree;

  for (int i = 10; i > 2; --i) {
    tree.insert(i, i);
  }

  tree.insert(0, 0);
  tree.insert(1, 1);
  //  auto tree = CreateSequancyTree();
  //  tree.insert(-1, -1);

  auto *root = tree.root();
  auto *rb_root = tree.GetRBNode(root);

  // clang-format off
            //                         7
            //                5                   9
            //         3(r)        6          8        10
            //    0         4
            //      1(r)
  // clang-format on
  checkNode(rb_root, 7, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_), 5, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_->right_), 6, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_->left_), 3, Color::Red);
  checkNode(tree.GetRBNode(rb_root->left_->left_->right_), 4, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_->left_->left_), 0, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_->left_->left_->right_), 1,
            Color::Red);

  checkNode(tree.GetRBNode(rb_root->right_), 9, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->left_), 8, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->right_), 10, Color::Black);

  EXPECT_EQ(tree.size(), 10);

  ///////////////////////////////////////////////

  tree.remove(4);

  // clang-format off
          //                         7
          //                5                   9
          //         1(r)        6          8        10
          //    0         3
          //
  // clang-format on
  checkNode(rb_root, 7, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_), 5, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_->right_), 6, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_->left_), 1, Color::Red);
  checkNode(tree.GetRBNode(rb_root->left_->left_->right_), 3, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_->left_->left_), 0, Color::Black);

  checkNode(tree.GetRBNode(rb_root->right_), 9, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->left_), 8, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->right_), 10, Color::Black);

  //  //  // leaves for 0 node
  EXPECT_EQ(rb_root->left_->left_->left_->left_, nullptr);
  EXPECT_EQ(rb_root->left_->left_->left_->right_, nullptr);

  //  // leaves for 3 node
  EXPECT_EQ(rb_root->left_->left_->right_->left_, nullptr);
  EXPECT_EQ(rb_root->left_->left_->right_->right_, nullptr);

  EXPECT_EQ(tree.size(), 9);
}

TEST_F(RemoveRedBlackTreeTest, remove_OneLeafEmptyCase_Test) {

  auto tree = CreateSequancyTree();
  tree.remove(8);

  auto *root = tree.root();
  auto *rb_root = tree.GetRBNode(root);

  // clang-format off
          //                         3
          //                1                5
          //             0    2          4        7
          //                                   6    9
          //
  // clang-format on
  checkNode(rb_root, 3, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_), 1, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_->left_), 0, Color::Black);
  checkNode(tree.GetRBNode(rb_root->left_->right_), 2, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_), 5, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->left_), 4, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->right_), 7, Color::Red);
  checkNode(tree.GetRBNode(rb_root->right_->right_->left_), 6, Color::Black);
  checkNode(tree.GetRBNode(rb_root->right_->right_->right_), 9, Color::Black);

  EXPECT_EQ(rb_root->right_->right_->right_->right_, nullptr);
  EXPECT_EQ(rb_root->right_->right_->right_->left_, nullptr);
  EXPECT_EQ(tree.size(), 9);
}

} // namespace bstree::test
