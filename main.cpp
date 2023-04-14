#include "BinaryTree.h"
#include <QCoreApplication>
#include <QDebug>
#include <istream>
#include <stdint.h>

int main(int argc, char *argv[]) {
  BinaryTree<int, char> tree;
  tree.insert(20, 'd');
  tree.insert(30, 'e');
  tree.insert(7, 'l');
  tree.insert(6, 'a');
  tree.insert(5, 'w');
  tree.insert(4, 's');
  tree.insert(3, 'z');
  tree.insert(10, 'f');
  tree.insert(31, 'v');
  tree.insert(40, 'p');
  tree.insert(39, 'e');
  tree.insert(38, 'x');
  tree.insert(50, ',');
  tree.insert(60, '/');
  tree.insert(49, ';');

  //  qDebug() << "tree size" << tree.size();
  //  auto ans = tree.find(7);
  //  qDebug() << ans->value_;
  tree.remove(7);
  //  //  tree.remove(6);
  //  ans = tree.find(3);
  //  qDebug() << ans->value_;

  for (const auto &elem : tree) {
    qDebug() << elem.first << "  " << elem.second;
  }

  qDebug() << "=======================================";
  //  tree.traverse();
  //  std::map<int, char> mapa;
  //  mapa.insert({20, 'd'});
  //  mapa.insert({30, 'e'});
  //  //  mapa.insert({7, 'l'});
  //  mapa.insert({6, 'a'});
  //  mapa.insert({5, 'w'});
  //  mapa.insert({4, 's'});
  //  mapa.insert({3, 'z'});
  //  mapa.insert({10, 'f'});
  //  mapa.insert({9, 'f'});

  //  for (auto &elem : mapa) {
  //    qDebug() << elem.first << "   " << elem.second;
  //  }

  return 0;
}
