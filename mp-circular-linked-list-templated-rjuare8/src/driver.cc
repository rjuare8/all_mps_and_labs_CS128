#include <iostream>

#include "circular-linked-list.hpp"

int main() {
  CircularLinkedList<int> cll;
  cll.InsertInOrder(4);
  cll.InsertInOrder(3);
  cll.InsertInOrder(3);
  cll.InsertInOrder(5);
  cll.InsertInOrder(8);
  cll.InsertInOrder(7);
  std::cout << cll << std::endl;

  // cll.~CircularLinkedList();
  // cll.InsertInOrder(78);

  /*CircularLinkedList<int> test3(cll);

  CircularLinkedList<int> test2;
  test2.InsertInOrder(15);
  test2.InsertInOrder(14);
  test2.InsertInOrder(13);
  test2 = cll;
  // test2 = test;
  // cll.InsertInOrder(10);
  // cll.InsertInOrder(13);
  // cll.InsertInOrder(11);
  // cll.InsertInOrder(14);
  std::cout << cll << std::endl;
  // std::cout << test << std::endl;
  std::cout << "Copy assigment operator test: " << test2 << std::endl;
  std::cout << "Copy constructor test:" << test3 << std::endl;
  // cll.Reverse();
  // std::cout << cll << std::endl;
  CircularLinkedList<int> reverse2;
  reverse2.InsertInOrder(12);
  reverse2.InsertInOrder(18);
  std::cout << reverse2 << std::endl;
  reverse2.Reverse();
  std::cout << reverse2 << std::endl;

  CircularLinkedList<int> reverse4;
  reverse4.InsertInOrder(1);
  reverse4.InsertInOrder(2);
  reverse4.InsertInOrder(3);
  reverse4.InsertInOrder(4);
  std::cout << reverse4 << std::endl;
  reverse4.Reverse();
  std::cout << reverse4 << std::endl;*/
}
