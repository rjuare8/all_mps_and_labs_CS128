#ifndef NODE_HPP
#define NODE_HPP

template <typename T1, typename T2>
struct Node {
  Node* parent = nullptr;
  Node* left = nullptr;
  Node* right = nullptr;
  T1 data;
  T2 key;
};

#endif