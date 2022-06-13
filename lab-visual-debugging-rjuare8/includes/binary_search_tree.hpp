/************************************************
 * Implement the functions we've asked of you in this file, directly
 * after our definition of the class template
 * BinarySearchTree.  That's all you have to do!
 ************************************************/

#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP

#include <iostream>
#include <vector>

#include "node.hpp"

template <typename T1, typename T2>
class BinarySearchTree {
public:
  // These are the declarations for member functions you'll define.
  void Merge(BinarySearchTree<T1, T2>& merge_in);
  void MergeHelper(Node<T1, T2>*& node);
  void Insert(Node<T1, T2>*& node);

  // Everything else has been defined for you in
  // binary_search_tree_more.hpp (in case you're interested)
  BinarySearchTree();
  BinarySearchTree(const T1& data, const T2& key);
  BinarySearchTree(const BinarySearchTree& source);
  BinarySearchTree& operator=(const BinarySearchTree& source) = delete;
  void Insert(const T1& data, const T2& key);
  void Clear();
  std::string ToStr() const;
  ~BinarySearchTree();

  template <typename U1, typename U2>
  friend std::ostream& operator<<(std::ostream& os,
                                  const BinarySearchTree<U1, U2>& bst);

private:
  Node<T1, T2>* root_ = nullptr;
  void Clear(Node<T1, T2>* n);
  void CopyHelper(const Node<T1, T2>* node);
  std::stringstream& ToSstream(Node<T1, T2>* n,
                               int depth,
                               std::string s,
                               std::stringstream& os) const;
};

// Here is where you'll define the member functions required.

template <typename T1, typename T2>
void BinarySearchTree<T1, T2>::Merge(BinarySearchTree<T1, T2>& merge_in) {
  MergeHelper(merge_in.root_);
  merge_in.root_ = nullptr;
}

template <typename T1, typename T2>
void BinarySearchTree<T1, T2>::MergeHelper(Node<T1, T2>*& node) {
  if (node == nullptr) {
    return;
  }

  MergeHelper(node->left);

  MergeHelper(node->right);

  std::cout << node->data << std::endl;

  Insert(node);
}

template <typename T1, typename T2>
void BinarySearchTree<T1, T2>::Insert(Node<T1, T2>*& node) {
  auto* iter = root_;
  auto* parent = root_;
  while (iter) {
    parent = iter;
    if (node->key < iter->key)
      iter = iter->left;
    else
      iter = iter->right;
  }
  if (node->key < parent->key)
    parent->left = node;
  else
    parent->right = node;
  node->parent = parent;
  node->right = nullptr;
  node->left = nullptr;
}

// Please do NOT remove or alter the line below this one!
#include "binary_search_tree_more.hpp"

#endif