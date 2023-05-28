# $${\color{red}Red  \space \color{black}-Black-Tree}$$ 
Implemented container that corresponds to Red Black Tree, similar to std::map. See reference https://en.cppreference.com/w/cpp/container/map
Base class is Binary Search Tree (see corresponding link https://www.geeksforgeeks.org/introduction-to-binary-search-tree-data-structure-and-algorithm-tutorials/)
Insert() and remove() methods were implemented according to these descriptions: see the links:https://www.geeksforgeeks.org/insertion-in-red-black-tree/  https://www.geeksforgeeks.org/deletion-in-red-black-tree/
Covered diference self-balanced cases of insert() and remove() methods by google unit tests.
At this time all definitions inside source files.
In main.cpp file container was compared with std::vector for search and insert methods and proved logN asymptotic complexity for find() a node method.
During container implementation it was also suitable to compare results with illustrations from https://www.cs.usfca.edu/~galles/visualization/RedBlack.html

To iterate thought the tree it was used Iterator Pattern from https://refactoring.guru/design-patterns/iterator (at this time it is implemented only for DFS (deph traversing).
