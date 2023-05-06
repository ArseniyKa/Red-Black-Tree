#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "BinaryTree.h"

enum class Color : int { Black = 0, Red = 1, Undefined = 2 };

template <typename T, typename M> struct RBNode : public Node<T, M> {
  Color color_{Color::Undefined};
};

template <typename T, typename M> class RedBlackTree : public BinaryTree<T, M> {
public:
  RedBlackTree();
  ~RedBlackTree();

  bool IsLeftSideOfNode(Node<T, M> *node);

  void LeftRotation(Node<T, M> *node);
  void RightRotation(Node<T, M> *node);

  void recolor(RBNode<T, M> *node);

  void insert(T key, M value) override;

  RBNode<T, M> *GetUncle(Node<T, M> *node);

  [[nodiscard]] Color GetColor(Node<T, M> *node) const;

private:
  void CreateLeftEdge(Node<T, M> *upper_node, Node<T, M> *lower_node);

  void CreateRightEdge(Node<T, M> *upper_node, Node<T, M> *lower_node);

  void TreeEmtyCase(T key, M value);

  void CreateNewNode(T key, M value, Node<T, M> *&node,
                     Node<T, M> *parent) override;

  RBNode<T, M> *GetRBNode(Node<T, M> *node) const;

  void RedParentCase(RBNode<T, M> *node);

  void RedParentRedUncleCase(RBNode<T, M> *node);
  void RedParentBlackUncleCase(RBNode<T, M> *node);

  void RightParentRightNodeCase(RBNode<T, M> *node);
  void RightParentLeftNodeCase(RBNode<T, M> *node);
  void LeftParentLeftNodeCase(RBNode<T, M> *node);
  void LeftParentRightNodeCase(RBNode<T, M> *node);
};

#endif // REDBLACKTREE_H
