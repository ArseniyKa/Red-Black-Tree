#ifndef BINARYTREEITERATOR_H
#define BINARYTREEITERATOR_H


#include <QCoreApplication>
#include <QDebug>
#include <istream>
#include <stdint.h>

template <typename T, typename M> struct Node {
    T key_; // ключ узла
    M value_; // значение узла
     Node<T, M> *left_{nullptr}; // указатель на левого потомка
    Node<T, M> *right_{nullptr}; // указатель на правого потомка
     Node<T, M> *parent_{nullptr}; // указатель на предка
};

template <typename T, typename M, typename TreeType> class
    BinaryTreeIterator {
public:
    BinaryTreeIterator(TreeType * tree, Node<T,M> * node): tree_(tree), node_(node){
        qDebug()<<"BinaryTreeIterator constructor";
    }

    ~BinaryTreeIterator(){
        qDebug()<<"BinaryTreeIterator destructor";
    }

      BinaryTreeIterator & operator++(){
         if (node_ == nullptr) {
            node_ = tree_->end_node_;
            return * this;
        }

        if (node_== tree_->end_node_){
            qDebug()<<"hey! i am here!";
            return * this;
        }

        if (node_->right_ != nullptr) {
            // find the smallest node on the right subtree
            // successor is the farthest left node of
            // right subtree
            node_ = node_->right_;

            while (node_->left_ != nullptr) {
                node_ = node_->left_;
            }
        } else {
            // finished with right subtree and there is no right
            // search up for first parent with a non-null right child
            // or nullptr,
            auto parent = node_->parent_;
            while (parent != nullptr && node_ == parent->right_) {
                node_ = parent;
                parent = parent->parent_;
            }
            node_ = parent;
        }
        return * this;
    }

    bool operator!=(const BinaryTreeIterator & other){
        return  node_ != other.node_;
    }

    bool operator==(const BinaryTreeIterator & other){
        return  node_ == other.node_;

    }


    std::pair<T,M> operator*(){
        //      if (node_==tree_->end_node_){
        //            return {0,0};
        //      }
        if (node_==nullptr){
            throw std::runtime_error("error in opearator*, node_ is nullptr");
        }
        auto pair = std::make_pair(node_->key_, node_->value_);
        return pair;
    }



private:

    Node<T,M> * Iterate(Node<T, M> *node) {
        if (node == nullptr) {
            return;
        }

        //        SubTranverse(node->left_);
        qDebug() << node->key_ << "   " << node->value_;
        if (node->right_ !=nullptr)
        {
            Iterate(node->right_);
        } else if (node->parent !=nullptr){
            node->parent_ !=nullptr;
        } else {
            throw std::runtime_error("error Iterate()");
        }
    }

    TreeType * tree_{nullptr};
    // as an index
    Node<T,M> * node_{nullptr};



};

#endif // BINARYTREEITERATOR_H
