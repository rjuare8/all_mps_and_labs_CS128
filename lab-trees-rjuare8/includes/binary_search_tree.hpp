#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "tree_node.hpp"

/******************************************************
 * CLASS DEFINITIONS + HELPER FUNCTION DECLARATIONS
 ******************************************************/

template <typename T>
class BinarySearchTree {
public:
  BinarySearchTree();
  BinarySearchTree(const BinarySearchTree& lhs) = delete;
  BinarySearchTree<T>& operator=(const BinarySearchTree& lhs) = delete;
  ~BinarySearchTree();

  /*
    Wrapper function to insert a value into the tree

    @param data the value to be inserted
    @return the root of the new tree
  */
  TreeNode<T>* InsertNode(const T& data);

  /*
    Wrapper function to delete a value from the tree

    @param data the value to be deleted
    @return the root of the new tree
  */
  TreeNode<T>* DeleteNode(const T& data);

  /*
    Wrapper function to calculate the height of the tree

    @return the height of the root of the tree
  */
  int GetHeight() const;

  /*
    Getter function for the root of the tree
  */
  TreeNode<T>* GetRoot() const;

  /*
    Allow overloaded output operator access to private data
  */
  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const BinarySearchTree<U>& bst);

private:
  TreeNode<T>* root_;

  /*
  Helper function to insert a node into the tree

  @param node the current tree node in the recursive call
  @param data the value to be inserted
  @return the root node of the new (sub)tree
  */
  TreeNode<T>* InsertNode(TreeNode<T>* node, const T& data);

  /*
  Helper function to delete a node in the tree

  @param node the current tree node in the recursive call
  @param data the value to be deleted
  @return the root of the (sub)tree
  */
  TreeNode<T>* DeleteNode(TreeNode<T>* node, const T& data);

  TreeNode<T>* FindMin(TreeNode<T>* node);

  /*
  Helper function to get the height of the tree

  @param node the current tree node in the recursive call
  @return the height of the current node
  */
  int GetHeight(TreeNode<T>* node) const;

  /*
  Helper function for destructor

  @param node the current tree node in the recursive call
  */
  void Clear(TreeNode<T>* node);

  /*
  Adds printable data for the tree into the output vector

  @param node the current tree node in the recursive call
  @param output the output vector which stores the list of strings to be
  printed
  @param left the number of offset characters from the left
  @param top the number of offset characters from the top
  @param width width of the output based on height of the tree
  */

  void AddPrintableData(TreeNode<T>* node,
                        std::vector<std::string>& output,
                        int left,
                        int top,
                        int width) const;
};

/*
  Declaration of overloaded operator<< for pretty printing of
  BinarySearchTree<T>
*/
// template <typename T>
// std::ostream& operator<<(std::ostream& os, const BinarySearchTree<T>& bst);

/******************************************************
 * MEMBER FUNCTION + HELPER FUNCTION DEFINITIONS
 ******************************************************/

template <typename T>
BinarySearchTree<T>::BinarySearchTree(): root_(nullptr) {}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::InsertNode(const T& data) {
  root_ = InsertNode(root_, data);
  return root_;
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::InsertNode(TreeNode<T>* node, const T& data) {
  bool insert = false;
  if (root_ == nullptr) {
    root_ = new TreeNode<T>(data);
    return root_;
  }
  if (data < node->data && node->left == nullptr) {
    node->left = new TreeNode<T>(data);
    insert = true;
  } else if (data >= node->data && node->right == nullptr) {
    node->right = new TreeNode<T>(data);
    insert = true;
  }

  if (insert) {
    return root_;
  }

  if (data < node->data && node->left != nullptr) {
    node = InsertNode(node->left, data);
  } else if (data >= node->data && node->right != nullptr) {
    node = InsertNode(node->right, data);
  }

  return root_;
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::DeleteNode(const T& data) {
  if (root_ == nullptr) {
    return nullptr;
  }

  root_ = DeleteNode(root_, data);
  return root_;
}

template <typename T>
void BinarySearchTree<T>::Clear(TreeNode<T>* node) {
  if (node) {
    Clear(node->left);
    Clear(node->right);
    delete node;
  }
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
  Clear(root_);
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::DeleteNode(TreeNode<T>* node, const T& data) {
  if (data < node->data) {
    node->left = DeleteNode(node->left, data);
  } else if (data > node->data) {
    node->right = DeleteNode(node->right, data);
  } else {
    if (node->left == nullptr && node->right == nullptr) {
      delete node;
      node = nullptr;

    } else if (node->left != nullptr && node->right == nullptr) {
      auto* tmp = node->left;
      delete node;
      node = tmp;
      tmp = nullptr;

    } else if (node->left == nullptr && node->right != nullptr) {
      auto* tmp = node->right;
      delete node;
      node = tmp;
      tmp = nullptr;

    } else {
      auto* tmp = FindMin(node);

      tmp->left = node->left;
      /*if (node->right == tmp) {
        tmp->right = node->right;
      }*/
      if (tmp == nullptr) {
        tmp->right = node->right;
      }
      // tmp->right = node->right;

      delete node;

      node = tmp;
      tmp = nullptr;
    }
  }

  return node;
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::FindMin(TreeNode<T>* node) {
  auto* parent = node->right;
  auto* current = node->right;

  while (current->left != nullptr) {
    parent = current;
    current = current->left;
  }

  if (current == node->right) {
    node->right = nullptr;

  } else {
    parent->left = current->right;

    current->right = nullptr;
  }

  // std::cout << "right node test " << node->data << std::endl;
  // std::cout << "parent test " << parent->data << std::endl;
  std::cout << "successor test " << current->data << std::endl;
  parent = nullptr;
  return current;
}

template <typename T>
int BinarySearchTree<T>::GetHeight() const {
  return GetHeight(root_);
}

template <typename T>
int BinarySearchTree<T>::GetHeight(TreeNode<T>* node) const {
  if (node == nullptr) {
    return -1;
  }
  return 1 + std::max(GetHeight(node->left), GetHeight(node->right));
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::GetRoot() const {
  return root_;
}
template <typename T>
std::ostream& operator<<(std::ostream& os, const BinarySearchTree<T>& bst) {
  size_t root_height = bst.GetHeight() + 1;
  std::vector<std::string> output(2 * root_height - 1);
  for (size_t i = 0; i < output.size(); i++) {
    output[i] = std::string((4 << root_height) + 1, ' ');
  }
  bst.AddPrintableData(bst.root_, output, 0, 0, (4 << root_height) - 3);
  for (size_t i = 0; i < output.size(); i++) {
    os << output[i] << std::endl;
  }
  return os;
}

template <typename T>
void BinarySearchTree<T>::AddPrintableData(TreeNode<T>* node,
                                           std::vector<std::string>& output,
                                           int left,
                                           int top,
                                           int curr_width) const {
  std::stringstream ss;
  std::string str;
  ss << node->data;
  ss >> str;

  int left_start_shift = 1 - (str.length() - 1) / 2;
  for (size_t i = 0;
       i < str.length() && left + curr_width / 2 + i < output[top].length();
       i++) {
    output[top][left + curr_width / 2 + left_start_shift + i] = str[i];
  }

  int branchOffset = (curr_width + 3) >> 3;

  int center = left + curr_width / 2;
  int leftcenter = left + (curr_width / 2 - 1) / 2;
  int rightcenter = left + curr_width / 2 + 2 + (curr_width / 2 - 1) / 2;

  if (node->left) {
    int branch_pos = center - branchOffset + 1;
    for (int pos = center + left_start_shift - 2; pos > branch_pos; pos--) {
      output[top][pos] = '_';
    }

    output[top + 1][branch_pos] = '/';
    for (int pos = branch_pos - 1; pos > leftcenter + 2; pos--) {
      output[top + 1][pos] = '_';
    }

    AddPrintableData(node->left, output, left, top + 2, curr_width / 2 - 1);
  }

  if (node->right) {
    int branch_pos = center + branchOffset + 1;
    for (int pos = center + left_start_shift + str.length() + 1;
         pos < branch_pos;
         pos++) {
      output[top][pos] = '_';
    }

    output[top + 1][branch_pos] = '\\';
    for (int pos = branch_pos + 1; pos < rightcenter; pos++) {
      output[top + 1][pos] = '_';
    }

    AddPrintableData(node->right,
                     output,
                     left + curr_width / 2 + 2,
                     top + 2,
                     curr_width / 2 - 1);
  }
}

#endif  // BINARYSEARCHTREE_HPP