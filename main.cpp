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
  BinaryTree() { qDebug() << "constructor was called"; };
  ~BinaryTree() { qDebug() << "destructor was called"; }
  BinaryTree(const BinaryTree &other) {
    qDebug() << "copy constructor was called";
  }
  BinaryTree &operator=(const BinaryTree &other) {
    qDebug() << "copy assignment was called";
  }

  void insert(T key, M value) {
    if (root_ == nullptr) {
      InitNode(key, value, root_, nullptr);
      return;
    }

    if (key < root_->key_) {
      SubInsert(key, value, root_->left_, root_);
    } else if (key > root_->key_) {
      SubInsert(key, value, root_->right_, root_);
    } else {
      root_->value_ = value;
    }
  }

  std::int64_t size() const { return size_; }

  M find(T key) {
    if (root_ == nullptr) {
      throw std::runtime_error("the tree is empty");
    }

    if (key < root_->key_) {
      return SubFind(key, root_->left_);
    } else if (key > root_->key_) {
      return SubFind(key, root_->right_);
    } else if (key == root_->key_) {
      return root_->value_;
    } else {
      throw std::runtime_error("undefined behavior in find()");
    }
  }

private:
  void SubInsert(T key, M value, Node<T, M> *&node, Node<T, M> *parent) {
    if (node == nullptr) {
      InitNode(key, value, node, parent);
      return;
    }

    if (key < node->key_) {
      SubInsert(key, value, node->left_, node);
    } else if (key > node->key_) {
      SubInsert(key, value, node->right_, node);
    }
  }

  M SubFind(T key, Node<T, M> *node) {
    if (node == nullptr) {
      throw std::runtime_error("the node is nullptr");
    }

    if (key < node->key_) {
      return SubFind(key, node->left_);
    } else if (key > node->key_) {
      return SubFind(key, node->right_);
    } else if (key == node->key_) {
      return node->value_;
    } else {
      throw std::runtime_error("undefined behavior in SubFind()");
    }
  }

  void InitNode(T key, M value, Node<T, M> *&node, Node<T, M> *parent) {
    node = new Node<T, M>;
    node->key_ = key;
    node->value_ = value;
    node->parent_ = parent;
    size_++;
  }

  std::int64_t size_{0};
  Node<T, M> *root_{nullptr};
};

int main(int argc, char *argv[]) {
  BinaryTree<int, char> tree;
  tree.insert(20, 'd');
  tree.insert(30, 'e');
  tree.insert(7, 'l');
  tree.insert(15, 'a');
  qDebug() << "tree size" << tree.size();
  auto ans = tree.find(15);
  qDebug() << ans;
  return 0;
}
