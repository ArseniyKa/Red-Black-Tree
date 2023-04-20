#include <gtest/gtest.h>

#include "RedBlackTree.h"
#include <cstdint>
#include <iostream>
#include <vector>
#include <string>

namespace bstree::test {

class RedBlackTreeTest : public testing::Test {
  protected:
    RedBlackTreeTest() = default;
};

TEST_F(RedBlackTreeTest, BSTreeIteratorTest) { // NOLINT
    RedBlackTree<int, std::string> tree;
//    std::map<int, char> mapa;

//    for (int i = 0; i < 20; i++) {
//        char symbol = i + 100;
//        tree.insert(i, symbol);
//        mapa.insert({i, symbol});
//    }

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
