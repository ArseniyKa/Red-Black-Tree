#include <QCoreApplication>
#include <QDebug>
#include <istream>

template <typename T, typename M> class BinaryTree {
public:
  struct Node {
    T key_; // ключ узла
    M value_;
    Node *left_{nullptr}; // указатель на левого потомка
    Node right_{nullptr}; // указатель на правого потомка
    Node parent_{nullptr}; // указатель на предк
  };

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
      root_ = new Node;
      root_->key_ = key;
      root_->value_ = value;
      return;
    }

    if (key < root_->key_) {
      LeftInsert(key, value);
    } else if (key > root_->key_) {
      RightInsert(key, value);
    } else {
      root_->value_ = value;
    }
  }

private:
  void LeftInsert(T key, M value) {
    Node *node = root_->left_;
    if (node == nullptr) {
      node = new Node;
    }

    node->insert(key, value);
  }

  void RightInsert(T key, M value) {
    Node *node = root_->left_;
    if (node == nullptr) {
      node = new Node;
    }

    node->insert(key, value);
  }

  Node *root_{nullptr};
};
int main(int argc, char *argv[]) { return 0; }
