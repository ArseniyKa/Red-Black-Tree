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

TEST_F(RedBlackTreeTest, LeftRotationTest) { // NOLINT
  RedBlackTree<int, std::string> tree;
  std::map<int, std::string> mapa;

  //  for (int i = 0; i < 20; i++) {
  //    std::string symbol = std::to_string(i + 100);
  //    mapa.insert({i, symbol});
  //  }

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

  tree.BinaryTree::insert(33, "root");
  tree.BinaryTree::insert(13, "wolf");
  tree.BinaryTree::insert(20, "cat");
  tree.BinaryTree::insert(37, "moon");
  tree.BinaryTree::insert(50, "X");
  tree.BinaryTree::insert(47, "alpha");
  tree.BinaryTree::insert(45, "alpha2");
  tree.BinaryTree::insert(43, "alpha3");
  tree.BinaryTree::insert(89, "Y");
  tree.BinaryTree::insert(92, "gamma");
  tree.BinaryTree::insert(99, "gamma2");
  tree.BinaryTree::insert(84, "beta");
  tree.BinaryTree::insert(82, "beta2");

  //    EXPECT_EQ(tree.size(), mapa.size());

  //    auto expected_itr = mapa.begin();
  //    auto itr = tree.begin();
  //    while (itr != tree.end() && expected_itr != mapa.end()) {
  //        auto symbol = (*(itr)).second;
  //        auto expected_symbol = (*(expected_itr)).second;
  //        std::cout << symbol << "\n";
  //        EXPECT_EQ(symbol, expected_symbol);
  //        ++expected_itr;
  //        ++itr;
  //    }
}

} // namespace bstree::test
