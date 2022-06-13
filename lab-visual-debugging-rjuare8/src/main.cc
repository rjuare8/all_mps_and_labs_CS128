#include <iostream>

#include "binary_search_tree.hpp"

int main() {
  // For fun... let's build a tree
  BinarySearchTree<int, int> bst1;
  bst1.Insert(20, 20);
  bst1.Insert(8, 8);
  bst1.Insert(22, 22);
  bst1.Insert(4, 4);
  std::cout << "bst1 : " << std::endl;
  std::cout << bst1.ToStr() << std::endl;

  BinarySearchTree<int, int> bst2;
  bst2.Insert(40, 40);
  bst2.Insert(20, 20);
  bst2.Insert(10, 10);
  bst2.Insert(60, 60);
  bst2.Insert(50, 50);
  bst2.Insert(40, 40);
  bst2.Insert(70, 70);
  std::cout << "bst2 : " << std::endl;
  std::cout << bst2.ToStr() << std::endl;

  bst1.Merge(bst2);
  std::cout << bst1.ToStr() << std::endl;
}
