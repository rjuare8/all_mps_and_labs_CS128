#ifndef BRANCHED_LINKED_LIST_HPP
#define BRANCHED_LINKED_LIST_HPP

#include <cstddef>
#include <stdexcept>
#include <string>

#include "node.hpp"

class BLL {
public:
  BLL() = default;
  BLL(const BLL& to_copy);
  ~BLL();

  BLL& operator=(const BLL& rhs);
  Node* PushBack(char dat);
  char GetAt(size_t idx) const;
  void SetAt(size_t idx, char dat);
  void Join(size_t idx, BLL* list);
  std::string ToString() const;
  size_t Size() const;

private:
  Node* head_ = nullptr;

  void Clear();
  bool IsBLLAcyclic() const;
  std::string ToStringRecursive(const BLL& bll) const;
  void JoinRecursive(size_t& idx, BLL* list, size_t& idx_list);
  void GetAtRecursive(size_t& idx, size_t& idx_list, char& value) const;
  void SetAtRecursive(size_t& idx, char& dat, size_t& idx_list) const;
};

#endif
