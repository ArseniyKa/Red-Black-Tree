#include <QCoreApplication>
#include <QDebug>
#include <istream>
#include <stdint.h>

template <typename T, typename M> class Node {
public:
  //    Node() { qDebug() << "constructor was called"; };
  //    ~Node() { qDebug() << "destructor was called"; }
  //    Node(const Node &other) {
  //    qDebug() << "copy constructor was called";
  //  }
  //    Node &operator=(const Node &other) {
  //    qDebug() << "copy assignment was called";
  //  }

  void insert(T key, M value) {

    // only for root
    if (parent_ == nullptr && left_ == nullptr && right_ == nullptr) {
      InitRoot(key, value);
      return;
    }

    if (key < key_) {
      LeftInsert(key, value);
    } else if (key > key_) {
      RightInsert(key, value);
    } else {
      value_ = value;
    }
  }

  static std::int64_t size() { return size_; }

  M find(T key) {
    M answer = '888';
    // only for root
    if (size_ == 0) {
      qDebug() << "the tree is empty";
      return answer;
    } else if (parent_ != nullptr && left_ == nullptr && right_ == nullptr) {
      qDebug() << "not found the key";
      return answer;
    }

    if (key < key_ && left_ != nullptr) {
      answer = left_->find(key);
    } else if (key > key_ && right_ != nullptr) {
      answer = right_->find(key);
      //    } else if (key < key_ && left_ == nullptr) {
      //      qDebug() << "not found left key";
      //    } else if (key > key_ && right_ == nullptr) {
      //      qDebug() << "not found right key";
    } else if (key == key_) {
      return value_;
    }

    return answer;
  }

  // private:
  void LeftInsert(T key, M value) {
    Node<T, M> *node = left_;

    // insert in that place
    if (node == nullptr) {
      InitNode(key, value, node);
      return;
    }

    node->insert(key, value);
  }

  void RightInsert(T key, M value) {
    Node<T, M> *node = right_;

    // insert in that place
    if (node == nullptr) {
      InitNode(key, value, node);
      return;
    }
    node->insert(key, value);
  }

  void InitNode(T key, M value, Node<T, M> *node) {
    node = new Node<T, M>;
    node->key_ = key;
    node->value_ = value;
    node->parent_ = this;
    size_++;
  }

  void InitRoot(T key, M value) {
    key_ = key;
    value_ = value;
    size_++;
  }

  T key_; // ключ узла
  M value_;
  Node<T, M> *left_{nullptr}; // указатель на левого потомка
  Node<T, M> *right_{nullptr}; // указатель на правого потомка
  Node<T, M> *parent_{nullptr}; // указатель на предка
  static std::int64_t size_;
};

template <typename T, typename M> std::int64_t Node<T, M>::size_ = 0;

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
      root_ = new Node<T, M>;
      root_->key_ = key;
      root_->value_ = value;
    }
  }

  Node<T, M> *root_{nullptr};
};

int main(int argc, char *argv[]) {
  BinaryTree<int, char> tree;
  tree.insert(20, 'd');
  tree.insert(30, 'e');
  tree.insert(15, 'a');
  tree.insert(7, 'l');
  qDebug() << tree.size();
  auto ans = tree.find(15);
  qDebug() << ans;
  return 0;
}
