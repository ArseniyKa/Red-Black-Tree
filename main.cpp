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

  Node<T, M> *&find(T key) {
    if (root_ == nullptr) {
      throw std::runtime_error("the tree is empty");
    }

    if (key < root_->key_) {
      return SubFind(key, root_->left_);
    } else if (key > root_->key_) {
      return SubFind(key, root_->right_);
    } else if (key == root_->key_) {
      return root_;
    } else {
      throw std::runtime_error("undefined behavior in find()");
    }
  }

  void remove(T key) {
    auto *node = find(key);
    auto *parent = node->parent_;
    if (node->left_ == nullptr && node->right_ == nullptr) {
      AllLeavesEmptyCase(node);
    } else if (node->right_ == nullptr) {
      RightLeafEmptyCase(node);
    } else if (node->right_ != nullptr) {
      RightChildCase(node);
    } else {
      throw std::runtime_error("undefined behavior in remove()");
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

  Node<T, M> *&SubFind(T key, Node<T, M> *node) {
    if (node == nullptr) {
      throw std::runtime_error("the node is nullptr");
    }

    if (key < node->key_) {
      return SubFind(key, node->left_);
    } else if (key > node->key_) {
      return SubFind(key, node->right_);
    } else if (key == node->key_) {
      return node;
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

  void NullParentLeaf(T key, Node<T, M> *parent) {
    if (parent->left_ != nullptr && key == parent->left_->key_) {
      parent->left_ == nullptr;
    } else if (parent->right_ != nullptr && key == parent->right_->key_) {
      parent->right_ == nullptr;
    } else {
      throw std::runtime_error("NullChildPointer error");
    }
  }

  void AllLeavesEmptyCase(Node<T, M> *&node) {
    auto key = node->key_;
    auto *parent = node->parent_;
    NullParentLeaf(key, parent);
    delete node;
    size_--;
  }

  void RightLeafEmptyCase(Node<T, M> *&node) {
    auto *parent = node->parent_;
    auto *left_child = node->left_;

    auto parent_key = parent->key_;
    auto key = node->key_;
    if (key < parent_key) {
      parent->left_ = left_child;
    } else {
      parent->right_ = left_child;
    }

    left_child->parent_ = parent;
    delete node;
    size_--;
  }

  void RightChildCase(Node<T, M> *&node) {
    auto *parent = node->parent_;
    auto parent_key = parent->key_;
    auto key = node->key_;
    auto *right_child = node->right_;

    auto *right_grandson = right_child->right_;
    auto *left_grandson = right_child->left_;

    if (left_grandson == nullptr) {

      if (key < parent_key) {
        parent->left_ = right_child;
      } else {
        parent->right_ = right_child;
      }

      right_child->parent_ = parent;

      auto *left_child = node->left_;
      right_child->left_ = left_child;
      left_child->parent_ = right_child;
    }

    delete node;
    size_--;
  }

  std::int64_t size_{0};
  Node<T, M> *root_{nullptr};
};

int main(int argc, char *argv[]) {
  BinaryTree<int, char> tree;
  tree.insert(20, 'd');
  tree.insert(30, 'e');
  tree.insert(7, 'l');
  tree.insert(6, 'a');
  tree.insert(5, 'w');
  tree.insert(4, 's');
  tree.insert(3, 'z');
  tree.insert(8, 'f');
  qDebug() << "tree size" << tree.size();
  auto ans = tree.find(7);
  qDebug() << ans->value_;
  tree.remove(7);
  tree.remove(6);
  ans = tree.find(3);

  return 0;
}
