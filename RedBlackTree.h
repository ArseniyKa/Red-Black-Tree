#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include "BinaryTree.h"

enum class Color: int {
    Black = 0,
    Red = 1,
    Undefined=2
};

template <typename T, typename M> struct RBNode : public Node<T,M>{
    Color color_{Color::Undefined};
};

template <typename T, typename M> class RedBlackTree : public BinaryTree<T,M> {
  public:
    RedBlackTree();
    ~RedBlackTree();

    bool IsLeftSideOfNode(Node<T, M> * node){
        if (node == nullptr){
            throw std::runtime_error("error in IsLeftSide. Node is nullptr");
        }

        auto * parent = node->parent_;

        if (parent == nullptr){
            throw std::runtime_error("error in IsLeftSide. parent is nullptr");
        }

        auto * left_parent_child = parent->left_;
        auto * right_parent_child = parent->right_;

        auto key = node->key_;

        if (left_parent_child!=nullptr && key == left_parent_child->key_){
            return true;
        } else if (right_parent_child!=nullptr && key == right_parent_child->key_){
            return false;
        } else {
             throw std::runtime_error("error in IsLeftSide. No one accepted condition");
        }

        return false;

    }


    void LeftRotation(Node<T, M> * node);
    void RightRotation(Node<T, M> * node);

  private:
    void CreateLeftEdge(Node<T, M> * upper_node, Node<T, M> * lower_node);

    void CreateRightEdge(Node<T, M> * upper_node, Node<T, M> * lower_node);


};



#endif // REDBLACKTREE_H
