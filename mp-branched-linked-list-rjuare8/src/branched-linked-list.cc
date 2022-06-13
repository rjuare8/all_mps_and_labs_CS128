#include "branched-linked-list.hpp"

#include <stdexcept>

BLL::BLL(const BLL& to_copy) {
  if (to_copy.head_ == nullptr) {
    head_ = nullptr;
  } else {
    auto* current_cop = to_copy.head_;
    head_ = new Node(to_copy.head_->data_);
    auto* current = head_;

    while (current_cop != nullptr) {
      if (current_cop->next_bll_ != nullptr) {
        current->next_bll_ = new BLL(*current_cop->next_bll_);
      }
      if (current_cop->next_node_ != nullptr)
        current->next_node_ = new Node(current_cop->next_node_->data_);

      current = current->next_node_;
      current_cop = current_cop->next_node_;
    }
  }
}

BLL::~BLL() { Clear(); }

void BLL::Clear() {
  if (head_ == nullptr) {
    return;
  }

  auto* current = head_;
  while (current != nullptr) {
    if (current->next_bll_ != nullptr) {
      delete current->next_bll_;

      current->next_bll_ = nullptr;
    }
    current = current->next_node_;
  }

  while (head_ != nullptr) {
    auto* next = head_->next_node_;
    delete head_;
    head_ = next;
  }
}

BLL& BLL::operator=(const BLL& rhs) {
  if (this == &rhs) {
    return *this;
  }
  this->~BLL();
  if (rhs.head_ == nullptr) {
    head_ = nullptr;
  } else {
    auto* current_cop = rhs.head_;
    head_ = new Node(rhs.head_->data_);
    auto* current = head_;

    while (current_cop != nullptr) {
      if (current_cop->next_bll_ != nullptr) {
        current->next_bll_ = new BLL(*current_cop->next_bll_);
      }
      if (current_cop->next_node_ != nullptr)
        current->next_node_ = new Node(current_cop->next_node_->data_);
      current = current->next_node_;
      current_cop = current_cop->next_node_;
    }
  }

  return *this;
}

Node* BLL::PushBack(char dat) {
  auto* to_insert = new Node(dat);
  if (head_ == nullptr) {
    head_ = to_insert;

    return to_insert;
  }
  Node* current = head_;
  while (current->next_node_ != nullptr) {
    current = current->next_node_;
  }

  current->next_node_ = to_insert;
  current = nullptr;
  return to_insert;
}

char BLL::GetAt(size_t idx) const {
  if (idx >= this->Size()) {
    throw std::runtime_error("index out of bounds");
  }
  size_t idx_list = 0;
  char value = ' ';
  GetAtRecursive(idx, idx_list, value);
  return value;
}

void BLL::GetAtRecursive(size_t& idx, size_t& idx_list, char& value) const {
  size_t idx_l = idx_list;
  auto* current = head_;
  while (current != nullptr) {
    if (idx_l == idx) {
      value = current->data_;
    }
    if (current->next_bll_ != nullptr) {
      idx_l++;
      current->next_bll_->GetAtRecursive(idx, idx_l, value);
    }

    idx_l++;
    current = current->next_node_;
  }
}

void BLL::SetAt(size_t idx, char dat) {
  if (idx >= this->Size()) {
    throw std::runtime_error("index out of bounds");
  }
  size_t idx_list = 0;
  SetAtRecursive(idx, dat, idx_list);
}

void BLL::SetAtRecursive(size_t& idx, char& dat, size_t& idx_list) const {
  size_t idx_l = idx_list;
  auto* current = head_;
  while (current != nullptr) {
    if (idx_l == idx) {
      current->data_ = dat;
    }
    if (current->next_bll_ != nullptr) {
      idx_l++;
      current->next_bll_->SetAtRecursive(idx, dat, idx_l);
    }

    idx_l++;
    current = current->next_node_;
  }
}

void BLL::Join(size_t idx, BLL* list) {
  size_t idx_list = 0;
  JoinRecursive(idx, list, idx_list);
}

void BLL::JoinRecursive(size_t& idx, BLL* list, size_t& idx_list) {
  size_t idx_l = idx_list;
  auto* current = head_;
  while (current != nullptr) {
    if (idx_l == idx) {
      if (current->next_bll_ != nullptr) {
        throw std::runtime_error(
            "Node in list contains already contains a bll");
      }
      current->next_bll_ = list;
      if (this->IsBLLAcyclic()) {
        current->next_bll_ = nullptr;
        throw std::runtime_error(
            "This join at this node would make BLL cyclic");
      }
      current = nullptr;
      return;
    }
    if (current->next_bll_ != nullptr) {
      current->next_bll_->JoinRecursive(idx, list, idx_l);
    }

    idx_l++;
    current = current->next_node_;
  }
}

std::string BLL::ToString() const {
  if (head_ == nullptr) return "";
  std::string rec_string;
  auto* current = this->head_;
  while (current != nullptr) {
    if (current->next_bll_ != nullptr) {
      rec_string += current->data_;
      rec_string += current->next_bll_->ToString();
    } else {
      rec_string += current->data_;
    }

    current = current->next_node_;
  }
  return rec_string;
}

std::string BLL::ToStringRecursive(const BLL& bll) const {
  std::string rec_string;
  auto* current = bll.head_;
  while (current != nullptr) {
    if (current->next_bll_ != nullptr) {
      rec_string += current->data_;
      rec_string += ToStringRecursive(*current->next_bll_);
    } else {
      rec_string += current->data_;
    }

    current = current->next_node_;
  }
  return rec_string;
}

size_t BLL::Size() const {
  size_t size = 0;
  auto* current = head_;
  while (current != nullptr) {
    size++;
    if (current->next_bll_ != nullptr) {
      size += current->next_bll_->Size();
    }

    current = current->next_node_;
  }

  return size;
}

bool BLL::IsBLLAcyclic() const {
  if (head_ == nullptr) {
    return false;
  }
  Node* shifu = nullptr;
  auto* oogway = head_;
  if (head_->next_bll_ != nullptr) {
    shifu = head_->next_bll_->head_;
  } else {
    shifu = head_->next_node_;
  }
  while (oogway != nullptr && shifu != nullptr &&
         (shifu->next_bll_ != nullptr || shifu->next_node_ != nullptr)) {
    // std::cout << "oogway data" << oogway->data_ << std::endl;
    // std::cout << "shifu data" << shifu->data_ << std::endl;
    if (oogway == shifu) {
      // std::cout << "it is cyclic" << std::endl;
      return true;
    }
    if (oogway->next_bll_ != nullptr) {
      oogway = oogway->next_bll_->head_;
    } else {
      oogway = oogway->next_node_;
    }
    if (shifu->next_bll_ != nullptr) {
      shifu = shifu->next_bll_->head_;
    } else {
      shifu = shifu->next_node_;
    }
    if (shifu->next_bll_ != nullptr) {
      shifu = shifu->next_bll_->head_;
    } else {
      shifu = shifu->next_node_;
    }
  }
  shifu = nullptr;
  oogway = nullptr;

  return false;
}