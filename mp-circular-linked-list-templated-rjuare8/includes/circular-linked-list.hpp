// clang-format off

#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  void InsertInOrder(const T& data);
  void InsertInOrderAsc(const T& data);
  void InsertInOrderDesc(const T& data);
  void Reverse();

  void Clear();

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);
  os << "head test: " << cll.head_->data << "tail test: " << cll.tail_->data << std::endl;
  return os;
}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  this->Clear();
}

template <typename T>
void CircularLinkedList<T>::Clear() {
  while (head_ != tail_) {
    Node<T>* next = head_->next;
    delete head_;
    head_ = next;
  }
  delete head_;
  head_ = nullptr; tail_ = nullptr;
}

template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) {
  if (source.head_ == nullptr) {
    head_ = nullptr; tail_ = nullptr; node_order_ = Order::kASC;
  } else if (source.head_ == source.tail_) {
    head_ = new Node<T>(source.head_->data);
    tail_ = head_;
    head_->next = head_;
    node_order_ = source.node_order_;
  } else {
    head_ = new Node<T>(source.head_->data);
    node_order_ = source.node_order_;
    Node<T>* curr_copy = head_;
    Node<T>* current = source.head_->next;
    while (current != source.head_) {
      auto* copy = new Node<T>(current->data);
      curr_copy->next = copy;
      if (current->next == source.head_) {
        tail_ = copy;
      }
      curr_copy = copy;
      current = current->next;
    }
    curr_copy->next = head_;
  }
}

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(const CircularLinkedList<T>& source) {
  
  if (this == &source) {
    return *this;
  }
  Clear();
  if (source.head_ == nullptr) {
    head_ = nullptr; tail_ = nullptr; node_order_ = Order::kASC;
  } else if (source.head_ == source.tail_) {
    head_ = new Node<T>(source.head_->data);
    tail_ = head_;
    head_->next = head_;
    node_order_ = source.node_order_;
  } else {
    head_ = new Node<T>(source.head_->data);
    node_order_ = source.node_order_;
    Node<T>* curr_copy = head_;
    Node<T>* current = source.head_->next;
    while (current != source.head_) {
      auto* copy = new Node<T>(current->data);
      curr_copy->next = copy;
      if (current->next == source.head_) {
        tail_ = copy;
      }
      curr_copy = copy;
      current = current->next;
    }
    curr_copy->next = head_;
  }
  return *this;
}

template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  if (head_ == nullptr) {
    auto to_insert = new Node<T>(data);
    head_ = to_insert;
    tail_ = to_insert;
    to_insert->next = head_;
  } else if (node_order_ == Order::kASC) {
    InsertInOrderAsc(data);
  } else if (node_order_ == Order::kDESC) {
    InsertInOrderDesc(data);
  }
}

template <typename T>
void CircularLinkedList<T>::InsertInOrderAsc(const T& data) {
  auto to_insert = new Node<T>(data);

  if (head_ == tail_) {
    std::cout << "test insert in a list with one node" << std::endl;
    if (data <= head_->data) {
      to_insert->next = tail_;
      head_->next = to_insert;
      head_ = to_insert;
    } else {
      to_insert->next = head_;
      head_->next = to_insert;
      tail_ = to_insert;
    }
    return;
  }

  if (data <= head_->data) {
    std::cout << "test data less than first" << std::endl;
    to_insert->next = head_;
    head_ = to_insert;
    tail_->next = head_;
    
  } else {
    Node<T>* current = head_;
    while (data >= current->next->data) {
      current = current->next;
      if (current == tail_) {
        std::cout << "test" << std::endl;
        to_insert->next = head_;
        tail_->next = to_insert;
        tail_ = tail_->next;
        return;
      }    
    }
    std::cout << "test" << std::endl;
    to_insert->next = current->next;
    current->next = to_insert;
  }
}

template <typename T>
void CircularLinkedList<T>::InsertInOrderDesc(const T& data) {
  auto to_insert = new Node<T>(data);

  if (head_ == tail_) {
    std::cout << "test insert in a list with one node" << std::endl;
    if (data >= head_->data) {
      to_insert->next = tail_;
      head_->next = to_insert;
      head_ = to_insert;
    } else {
      to_insert->next = head_;
      head_->next = to_insert;
      tail_ = to_insert;
    }
    return;
  }

  if (data >= head_->data) {
    std::cout << "test data less than first" << std::endl;
    to_insert->next = head_;
    head_ = to_insert;
    tail_->next = head_;
    
  } else {
    Node<T>* current = head_;
    while (data <= current->next->data) {
      current = current->next;
      if (current == tail_) {
        std::cout << "test" << std::endl;
        to_insert->next = head_;
        tail_->next = to_insert;
        tail_ = tail_->next;
        return;
      }    
    }
    std::cout << "test" << std::endl;
    to_insert->next = current->next;
    current->next = to_insert;
  }
}




template <typename T>
void CircularLinkedList<T>::Reverse() {
  if (node_order_ == Order::kASC) {
    node_order_ = Order::kDESC;
  } else {
    node_order_ = Order::kASC;
  }

  if (head_ == nullptr || head_ == tail_) {
    return;
  }

  if (head_->next == tail_) {
    std::cout << "test two nodes" << std::endl;
    head_ = tail_;
    tail_ = tail_->next;
    return;
  }

  Node<T>* prev = head_;
  Node<T>* change_next = head_->next;
  Node<T>* current = head_->next->next;
  while (current != head_->next) {
    change_next->next = prev;
    prev = change_next;
    change_next = current;
    std::cout << current->data << std::endl;
    current = current->next;
  }
  head_->next = tail_;
  tail_ = head_;
  head_ = head_->next;
  prev = nullptr; change_next = nullptr; current = nullptr;
}



#endif