/************************************************
This file contains definitions for behaviors you're
not required to implement! You can ignore its contents!
************************************************/

#ifndef BINARY_SEARCH_TREE_OTHER_HPP
#define BINARY_SEARCH_TREE_OTHER_HPP
#include <sstream>
#include <stack>

#include "binary_search_tree.hpp"

template <typename T1, typename T2>
BinarySearchTree<T1, T2>::BinarySearchTree(): root_(nullptr) {}

template <typename T1, typename T2>
BinarySearchTree<T1, T2>::BinarySearchTree(const T1& data, const T2& key):
    root_(nullptr) {
  auto* tmp = new Node<T1, T2>;
  tmp->data = data;
  tmp->key = key;
  root_ = tmp;
}

template <typename T1, typename T2>
BinarySearchTree<T1, T2>::BinarySearchTree(const BinarySearchTree& source) {
  if (source.root_ != nullptr) CopyHelper(source.root_);
}

template <typename T1, typename T2>
void BinarySearchTree<T1, T2>::CopyHelper(const Node<T1, T2>* node) {
  Insert(node->data, node->key);
  if (node->left != nullptr) CopyHelper(node->left);
  if (node->right != nullptr) CopyHelper(node->right);
}

template <typename T1, typename T2>
void BinarySearchTree<T1, T2>::Insert(const T1& data, const T2& key) {
  auto new_node = new Node<T1, T2>;
  new_node->data = data;
  new_node->key = key;
  if (root_ == nullptr) {
    root_ = new_node;
    return;
  }

  auto* iter = root_;
  auto* parent = root_;
  while (iter) {
    parent = iter;
    if (key < iter->key)
      iter = iter->left;
    else
      iter = iter->right;
  }
  if (key < parent->key)
    parent->left = new_node;
  else
    parent->right = new_node;
  new_node->parent = parent;
}

template <typename T1, typename T2>
BinarySearchTree<T1, T2>::~BinarySearchTree() {
  Clear();
}

template <typename T1, typename T2>
void BinarySearchTree<T1, T2>::Clear() {
  Clear(root_);
  root_ = nullptr;
}

template <typename T1, typename T2>
void BinarySearchTree<T1, T2>::Clear(Node<T1, T2>* n) {
  if (n != nullptr) {
    Clear(n->left);
    Clear(n->right);
    delete n;
  }
}

template <typename T1, typename T2>
std::string BinarySearchTree<T1, T2>::ToStr() const {
  std::stringstream ss;
  return (ToSstream(root_, 0, "", ss)).str();
}

// output
template <typename T1, typename T2>
std::stringstream& BinarySearchTree<T1, T2>::ToSstream(
    Node<T1, T2>* n, int depth, std::string s, std::stringstream& os) const {
  if (n == nullptr) {
    os << "Empty" << std::endl;
    return os;
  }
  os << " " << n->key << " (" << n->data << ")\n";
  os << s << " `--[L]";
  s += " |  ";
  if (n->left)
    ToSstream(n->left, depth + 1, s, os);
  else
    os << " nullptr\n";
  s.erase(s.end() - 4, s.end());

  os << s << " `--[R]";
  s += " |  ";
  if (n->right)
    ToSstream(n->right, depth + 1, s, os);
  else
    os << " nullptr\n";
  s.erase(s.end() - 4, s.end());
  return os;
}

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const BinarySearchTree<T1, T2>& bst);

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os,
                         const BinarySearchTree<T1, T2>& bst) {
  std::stack<Node<T1, T2>*> stack;
  auto* iter = bst.root_;
  while (iter != nullptr || !stack.empty()) {
    while (iter) {
      stack.push(iter);
      iter = iter->left;
    }
    iter = stack.top();
    stack.pop();
    os << iter->data << " ";
    iter = iter->right;
  }
  return os;
}

#endif