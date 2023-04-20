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


    void LeftRotation(Node<T, M> * node) {
        if (this->size_<2){
            throw std::runtime_error("error in LeftRotation");
        }

        auto * parent = node->parent_;
        auto * right_child = node->right_;

        auto * left_child_of_right_child = right_child->left_;

        bool node_is_left = IsLeftSideOfNode(node);
        if (node_is_left) {
            parent->left_ = right_child;
        } else {
            parent->right_ = right_child;
        }

        right_child->parent_ = parent;

        node->right_ = left_child_of_right_child;
        left_child_of_right_child->parent_ =node;

        node->parent_ = right_child;
        right_child->left_ = node;

    }

};



#endif // REDBLACKTREE_H
