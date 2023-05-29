#include <gtest/gtest.h>

#include "BinaryTree.h"
#include <cstdint>
#include <iostream>
#include <vector>

namespace bstree::test {

class BinarySearchTest : public testing::Test {
protected:
  BinarySearchTest() = default;

  // clang-format off
  //                               root
  //                left_sub_root        right_sub_root
  //    left_sub_sub_root                                 parent
  //                                                                 X
  //                                                     alpha                    Y
  //                                                alpha2                 beta        gamma
  //                                         alpha3                    beta2               gamma2
  //
  //
  //
  // clang-format on
  BinaryTree<int, std::string> stringTree() {
    BinaryTree<int, std::string> tree;

    tree.insert(33, "root");
    tree.insert(13, "left_sub_root");
    tree.insert(10, "left_sub_sub_root");
    tree.insert(34, "right_sub_root");
    tree.insert(37, "parent");
    tree.insert(50, "X");
    tree.insert(47, "alpha");
    tree.insert(45, "alpha2");
    tree.insert(43, "alpha3");
    tree.insert(89, "Y");
    tree.insert(92, "gamma");
    tree.insert(99, "gamma2");
    tree.insert(84, "beta");
    tree.insert(82, "beta2");

    return tree;
  }

  template <typename T, typename M>
  void checkNode(Node<T, M> *node, T true_key, M true_value) {
    EXPECT_EQ(node->key_, true_key);
    EXPECT_EQ(node->value_, true_value);
  }
};

TEST_F(BinarySearchTest, insertTest) { // NOLINT

  auto tree = stringTree();
  auto *root = tree.root();

  checkNode(root, 33, std::string("root"));
  checkNode(root->left_, 13, std::string("left_sub_root"));
  checkNode(root->left_->left_, 10, std::string("left_sub_sub_root"));
  checkNode(root->right_, 34, std::string("right_sub_root"));
  checkNode(root->right_->right_, 37, std::string("parent"));
  checkNode(root->right_->right_->right_, 50, std::string("X"));
  checkNode(root->right_->right_->right_->left_, 47, std::string("alpha"));
  checkNode(root->right_->right_->right_->left_->left_, 45,
            std::string("alpha2"));
  checkNode(root->right_->right_->right_->left_->left_->left_, 43,
            std::string("alpha3"));
  checkNode(root->right_->right_->right_->right_, 89, std::string("Y"));
  checkNode(root->right_->right_->right_->right_->right_, 92,
            std::string("gamma"));
  checkNode(root->right_->right_->right_->right_->right_->right_, 99,
            std::string("gamma2"));
  checkNode(root->right_->right_->right_->right_->left_, 84,
            std::string("beta"));
  checkNode(root->right_->right_->right_->right_->left_->left_, 82,
            std::string("beta2"));
}

TEST_F(BinarySearchTest, findTest) { // NOLINT

  auto tree = stringTree();

  auto ans = tree.find(50);
  EXPECT_EQ(ans->value_, "X");
  EXPECT_EQ(ans->parent_->value_, "parent");
  EXPECT_EQ(ans->left_->value_, "alpha");
  EXPECT_EQ(ans->right_->value_, "Y");

  ans = tree.find(82);
  EXPECT_EQ(ans->value_, "beta2");

  ans = tree.find(33);
  EXPECT_EQ(ans->value_, "root");
}

TEST_F(BinarySearchTest, remove_AllLeavesEmptyCase_Test) { // NOLINT
  auto tree = stringTree();
  auto *root = tree.root();
  EXPECT_EQ(tree.size(), 14);

  tree.remove(82);
  checkNode(root, 33, std::string("root"));
  checkNode(root->left_, 13, std::string("left_sub_root"));
  checkNode(root->left_->left_, 10, std::string("left_sub_sub_root"));
  checkNode(root->right_, 34, std::string("right_sub_root"));
  checkNode(root->right_->right_, 37, std::string("parent"));
  checkNode(root->right_->right_->right_, 50, std::string("X"));
  checkNode(root->right_->right_->right_->left_, 47, std::string("alpha"));
  checkNode(root->right_->right_->right_->left_->left_, 45,
            std::string("alpha2"));
  checkNode(root->right_->right_->right_->left_->left_->left_, 43,
            std::string("alpha3"));
  checkNode(root->right_->right_->right_->right_, 89, std::string("Y"));
  checkNode(root->right_->right_->right_->right_->right_, 92,
            std::string("gamma"));
  checkNode(root->right_->right_->right_->right_->right_->right_, 99,
            std::string("gamma2"));
  checkNode(root->right_->right_->right_->right_->left_, 84,
            std::string("beta"));

  EXPECT_EQ(root->right_->right_->right_->right_->left_->left_, nullptr);
  EXPECT_EQ(tree.size(), 13);
}

TEST_F(BinarySearchTest, remove_RightLeafEmptyCase_Test) { // NOLINT
  auto tree = stringTree();
  auto *root = tree.root();
  EXPECT_EQ(tree.size(), 14);

  tree.remove(47);
  checkNode(root, 33, std::string("root"));
  checkNode(root->left_, 13, std::string("left_sub_root"));
  checkNode(root->left_->left_, 10, std::string("left_sub_sub_root"));
  checkNode(root->right_, 34, std::string("right_sub_root"));
  checkNode(root->right_->right_, 37, std::string("parent"));
  checkNode(root->right_->right_->right_, 50, std::string("X"));
  checkNode(root->right_->right_->right_->left_, 45, std::string("alpha2"));
  checkNode(root->right_->right_->right_->left_->left_, 43,
            std::string("alpha3"));
  checkNode(root->right_->right_->right_->right_, 89, std::string("Y"));
  checkNode(root->right_->right_->right_->right_->right_, 92,
            std::string("gamma"));
  checkNode(root->right_->right_->right_->right_->right_->right_, 99,
            std::string("gamma2"));
  checkNode(root->right_->right_->right_->right_->left_, 84,
            std::string("beta"));

  EXPECT_EQ(tree.size(), 13);
}

TEST_F(BinarySearchTest,
       remove_RightChildCase_LeftGrandsonNull_Test) { // NOLINT
  auto tree = stringTree();
  auto *root = tree.root();
  EXPECT_EQ(tree.size(), 14);

  tree.remove(89); // remove Y
  checkNode(root, 33, std::string("root"));
  checkNode(root->left_, 13, std::string("left_sub_root"));
  checkNode(root->left_->left_, 10, std::string("left_sub_sub_root"));
  checkNode(root->right_, 34, std::string("right_sub_root"));
  checkNode(root->right_->right_, 37, std::string("parent"));
  checkNode(root->right_->right_->right_, 50, std::string("X"));
  checkNode(root->right_->right_->right_->left_, 47, std::string("alpha"));
  checkNode(root->right_->right_->right_->left_->left_, 45,
            std::string("alpha2"));
  checkNode(root->right_->right_->right_->left_->left_->left_, 43,
            std::string("alpha3"));
  checkNode(root->right_->right_->right_->right_, 92, std::string("gamma"));
  checkNode(root->right_->right_->right_->right_->right_, 99,
            std::string("gamma2"));
  checkNode(root->right_->right_->right_->right_->left_, 84,
            std::string("beta"));
  checkNode(root->right_->right_->right_->right_->left_->left_, 82,
            std::string("beta2"));

  EXPECT_EQ(tree.size(), 13);
}

TEST_F(BinarySearchTest,
       remove_RightChildCase_LeftGrandsonNotNull_Test) { // NOLINT
  auto tree = stringTree();
  auto *root = tree.root();
  EXPECT_EQ(tree.size(), 14);

  tree.remove(50);
  checkNode(root, 33, std::string("root"));
  checkNode(root->left_, 13, std::string("left_sub_root"));
  checkNode(root->left_->left_, 10, std::string("left_sub_sub_root"));
  checkNode(root->right_, 34, std::string("right_sub_root"));
  checkNode(root->right_->right_, 37, std::string("parent"));
  checkNode(root->right_->right_->right_, 82, std::string("beta2"));
  checkNode(root->right_->right_->right_->left_, 47, std::string("alpha"));
  checkNode(root->right_->right_->right_->left_->left_, 45,
            std::string("alpha2"));
  checkNode(root->right_->right_->right_->left_->left_->left_, 43,
            std::string("alpha3"));
  checkNode(root->right_->right_->right_->right_, 89, std::string("Y"));
  checkNode(root->right_->right_->right_->right_->right_, 92,
            std::string("gamma"));
  checkNode(root->right_->right_->right_->right_->right_->right_, 99,
            std::string("gamma2"));
  checkNode(root->right_->right_->right_->right_->left_, 84,
            std::string("beta"));

  EXPECT_EQ(root->right_->right_->right_->right_->left_->left_, nullptr);
  EXPECT_EQ(tree.size(), 13);
}

TEST_F(BinarySearchTest, BSTreeIteratorTest) { // NOLINT
  BinaryTree<int, char> tree;
  std::map<int, char> mapa;

  for (int i = 0; i < 20; i++) {
    char symbol = i + 100;
    tree.insert(i, symbol);
    mapa.insert({i, symbol});
  }

  EXPECT_EQ(tree.size(), mapa.size());

  auto expected_itr = mapa.begin();
  auto itr = tree.begin();
  while (itr != tree.end() && expected_itr != mapa.end()) {
    auto symbol = (*(itr)).second;
    auto expected_symbol = (*(expected_itr)).second;
    //    std::cout << symbol << "\n";
    EXPECT_EQ(symbol, expected_symbol);
    ++expected_itr;
    ++itr;
  }

  // use iterators several times
  int val = 0;
  for (auto elem : tree) {
    EXPECT_EQ(elem.first, val++);
  }

  val = 0;
  for (auto elem : tree) {
    EXPECT_EQ(elem.first, val++);
  }

  val = 0;
  for (auto elem : tree) {
    EXPECT_EQ(elem.first, val++);
  }
}

TEST_F(BinarySearchTest, CopyConstructorTest) { // NOLINT

  BinaryTree<int, int> old_tree;

  for (int i = 0; i < 10; i++) {
    old_tree.insert(i, i);
  }

  auto new_tree1 = old_tree;
  BinaryTree<int, int> new_tree2(old_tree);
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
}

} // namespace bstree::test
