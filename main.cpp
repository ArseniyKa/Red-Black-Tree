#include "BinaryTree.h"
#include "RedBlackTree.h"
#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <stdint.h>

#include <chrono>

int main(int argc, char *argv[]) {

  using std::chrono::duration;
  using std::chrono::duration_cast;
  using std::chrono::high_resolution_clock;
  using std::chrono::milliseconds;

  std::vector<int> container;
  RedBlackTree<int, int> tree;

  int size = 1e7;

  for (int i = 0; i < size; i++) {
    tree.insert(i, i); // 39499 ms for 1e7
    //    container.push_back(i); // 74.8087 ms for 1e7
  }

  auto t1 = high_resolution_clock::now();
  auto value = tree.find(size / 2); // 0.004889ms for 1e7
  /*auto result1 =
      std::find(container.begin(), container.end(), size / 2);*/ // 16.1718 ms
  auto t2 = high_resolution_clock::now();

  /* Getting number of milliseconds as a double. */
  duration<double, std::milli> ms_double = t2 - t1;

  std::cout << ms_double.count() << "ms\n";

  //  std::cout << "value\n";
  //  2);

  return 0;
}
