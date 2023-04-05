#ifndef BINARYTREE_H
#define BINARYTREE_H


#include <QCoreApplication>
#include <QDebug>
#include <istream>
#include <stdint.h>

template <typename T, typename M> struct Node {
    T key_; // ключ узла
    M value_;
    Node<T, M> *left_{nullptr}; // указатель на левого потомка
    Node<T, M> *right_{nullptr}; // указатель на правого потомка
    Node<T, M> *parent_{nullptr}; // указатель на предка
};

template <typename T, typename M> class BinaryTree {
public:
    BinaryTree();;
    ~BinaryTree();
    BinaryTree(const BinaryTree &other);
    BinaryTree &operator=(const BinaryTree &other);

    void insert(T key, M value);

    std::int64_t size() const;

    Node<T, M> *&find(T key);

    void remove(T key);

    void traverse();

private:
    void SubInsert(T key, M value, Node<T, M> *&node, Node<T, M> *parent);

    Node<T, M> *&SubFind(T key, Node<T, M> *node);

    void InitNode(T key, M value, Node<T, M> *&node, Node<T, M> *parent);

    void NullParentLeaf(T key, Node<T, M> *parent);

    void AllLeavesEmptyCase(Node<T, M> *&node);

    void RightLeafEmptyCase(Node<T, M> *&node);

    void RightChildCase(Node<T, M> *&node);

    void LeftGrandsonNull(Node<T, M> *&node);

    void LeftGrandsonNotNull(Node<T, M> *&node);

    Node<T, M> *&FindMinimalSubTreeChild(Node<T, M> *&node);

    void SubTranverse(Node<T, M> *node);

    std::int64_t size_{0};
    Node<T, M> *root_{nullptr};
};



#endif // BINARYTREE_H
