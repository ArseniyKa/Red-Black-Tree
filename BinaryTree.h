#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <stdint.h>

#include <QCoreApplication>
#include <QDebug>
#include <istream>

#include "BinaryTreeIterator.h"

template <typename T, typename M> class BinaryTree {
public:
  BinaryTree();
  ~BinaryTree();
  BinaryTree(const BinaryTree &other);
  BinaryTree &operator=(const BinaryTree &other);

  virtual void insert(T key, M value);

  std::int64_t size() const;

  Node<T, M> *&find(T key);

  void remove(T key);

  void traverse();

  BinaryTreeIterator<T, M, BinaryTree<T, M>> begin();
  BinaryTreeIterator<T, M, BinaryTree<T, M>> end();

  Node<T, M> *end_node_{nullptr};

  [[nodiscard]] Node<T, M> *root() const;

  [[nodiscard]] bool IsLeftSideOfNode(Node<T, M> *node) const;

protected:
  void SubInsert(T key, M value, Node<T, M> *&node, Node<T, M> *parent);

  Node<T, M> *&SubFind(T key, Node<T, M> *node);

  virtual void CreateNewNode(T key, M value, Node<T, M> *&node,
                             Node<T, M> *parent);

  virtual Node<T, M> *AllLeavesEmptyCase(Node<T, M> *&node);
  virtual Node<T, M> *OneLeafEmptyCase(Node<T, M> *&node);
  Node<T, M> *AllLeavesCase(Node<T, M> *&node);

  void ErrorMessage(const std::string &message) const;

  Node<T, M> *&FindMinimalSubTreeChild(Node<T, M> *&node);

  Node<T, M> *FindLastTreeNode(Node<T, M> *node);

  void CreateLeftEdge(Node<T, M> *upper_node, Node<T, M> *lower_node);

  void CreateRightEdge(Node<T, M> *upper_node, Node<T, M> *lower_node);

  void SubTranverse(Node<T, M> *node);

  void CheckNode(Node<T, M> *node, const std::string &function_name,
                 const std::string &node_name) const;

  void ReasignParentChild(Node<T, M> *old_child, Node<T, M> *new_child);

  void CopySuccessor(Node<T, M> *node, Node<T, M> *successor);

  std::int64_t size_{0};
  Node<T, M> *root_{nullptr};
};

#endif // BINARYTREE_H
