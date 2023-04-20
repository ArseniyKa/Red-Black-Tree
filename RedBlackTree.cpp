#include "RedBlackTree.h"
#include <string>

template <typename T, typename M> RedBlackTree<T, M>::RedBlackTree() {
  qDebug() << "Red Black tree constructor";
}

template <typename T, typename M> RedBlackTree<T, M>::~RedBlackTree() {
  qDebug() << "Red Black tree destructor";
}

// explicit instantiation
template class RedBlackTree<int, std::string>;
