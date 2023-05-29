#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "BinaryTree.h"

enum class Color : int { Black = 0, Red = 1, Undefined = 2 };

template <typename T, typename M> struct RBNode : public Node<T, M> {
  Color color_{Color::Undefined};
};

template <typename T, typename M> class RedBlackTree : public BinaryTree<T, M> {
public:
  RedBlackTree() = default;
  ~RedBlackTree() = default;

  RedBlackTree(const RedBlackTree &other);
  RedBlackTree &operator=(const RedBlackTree &other);

  RedBlackTree(RedBlackTree &&other);
  RedBlackTree &operator=(RedBlackTree &&other);

  void LeftRotation(Node<T, M> *node);
  void RightRotation(Node<T, M> *node);

  void recolor(RBNode<T, M> *node);

  void insert(T key, M value) override;

  RBNode<T, M> *GetUncle(Node<T, M> *node);

  RBNode<T, M> *GetRBNode(Node<T, M> *node) const;

  RBNode<T, M> *GetSibling(Node<T, M> *node);

private:
  void TreeEmtyCase(T key, M value);

  void CreateNewNode(T key, M value, Node<T, M> *&node,
                     Node<T, M> *parent) override;

  void RedParentCase(RBNode<T, M> *node);

  void RedParentRedUncleCase(RBNode<T, M> *node);
  void RedParentBlackUncleCase(RBNode<T, M> *node);

  void RightParentRightNodeCase(RBNode<T, M> *node);
  void RightParentLeftNodeCase(RBNode<T, M> *node);
  void LeftParentLeftNodeCase(RBNode<T, M> *node);
  void LeftParentRightNodeCase(RBNode<T, M> *node);

  void CheckColor(const Color color);
  bool IsRedNode(Node<T, M> *node) const;

  ///@brief this methods for remove case:
  Node<T, M> *OneLeafEmptyCase(Node<T, M> *&node) override;
  Node<T, M> *AllLeavesEmptyCase(Node<T, M> *&node) override;

  Node<T, M> *DoubleBlackCase(Node<T, M> *node);

  Node<T, M> *RedSiblingCase(Node<T, M> *node, Node<T, M> *sibling);
  Node<T, M> *BlackSiblingCase(Node<T, M> *node, Node<T, M> *sibling);

  Node<T, M> *BlackSiblingBlackNephews(RBNode<T, M> *node,
                                       RBNode<T, M> *sibling);

  Node<T, M> *BlackSiblingRedNephew(RBNode<T, M> *node, RBNode<T, M> *sibling);
};

#endif // REDBLACKTREE_H
