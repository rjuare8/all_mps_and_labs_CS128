#include <iomanip>
#include <sstream>
#include <stdexcept>
using std::endl;
using std::ostream;
using std::ostringstream;
using std::setfill;
using std::setw;
using std::string;

#include "doubly_linked_list.hpp"

DoublyLinkedList::DoublyLinkedList(char val) {
  Node* first = new Node(val);
  head_ = first;
  tail_ = first;
  size_ = 1;
}

DoublyLinkedList::DoublyLinkedList(const std::vector<char>& values) {
  if (values.empty()) {
    DoublyLinkedList();
  } else {
    std::vector<Node*> vect_nod = {};
    for (size_t i = 0; i < values.size(); i++) {
      Node* val = new Node(values.at(i));
      vect_nod.push_back(val);
    }

    head_ = vect_nod.at(0);
    tail_ = vect_nod.at(0);
    size_ = 1;

    for (size_t i = 1; i < vect_nod.size(); i++) {
      vect_nod.at(i)->prev = vect_nod.at(i - 1);
      vect_nod.at(i - 1)->next = vect_nod.at(i);

      tail_ = vect_nod.at(i);
      size_++;
    }
  }
}

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& rhs) {
  if (rhs.size_ == 0) {
    // call destructor

    DoublyLinkedList();
  } else {
    // call destructor

    Node* current = rhs.head_;
    std::vector<char> vect_vals = {};
    while (current != nullptr) {
      vect_vals.push_back(current->data);
      current = current->next;
    }

    std::vector<Node*> vect_nod = {};
    for (size_t i = 0; i < vect_vals.size(); i++) {
      Node* val = new Node(vect_vals.at(i));
      vect_nod.push_back(val);
    }

    head_ = vect_nod.at(0);
    tail_ = vect_nod.at(0);
    size_++;

    for (size_t i = 1; i < vect_nod.size(); i++) {
      vect_nod.at(i)->prev = vect_nod.at(i - 1);
      vect_nod.at(i - 1)->next = vect_nod.at(i);

      tail_ = vect_nod.at(i);
      size_++;
    }
  }
}

DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& rhs) {
  if (this == &rhs) {
    return *this;
  }

  if (rhs.size_ == 0) {
    // call destructor

    Clear();
    DoublyLinkedList();
  } else {
    Clear();

    Node* current = rhs.head_;
    std::vector<char> vect_vals = {};
    while (current != nullptr) {
      vect_vals.push_back(current->data);
      current = current->next;
    }

    std::vector<Node*> vect_nod = {};
    for (size_t i = 0; i < vect_vals.size(); i++) {
      Node* val = new Node(vect_vals.at(i));
      vect_nod.push_back(val);
    }

    head_ = vect_nod.at(0);
    tail_ = vect_nod.at(0);
    size_++;

    for (size_t i = 1; i < vect_nod.size(); i++) {
      vect_nod.at(i)->prev = vect_nod.at(i - 1);
      vect_nod.at(i - 1)->next = vect_nod.at(i);

      tail_ = vect_nod.at(i);
      size_++;
    }
  }
  return *this;
}

DoublyLinkedList::~DoublyLinkedList() { Clear(); }

void DoublyLinkedList::Clear() {
  while (head_ != nullptr) {
    Node* next = head_->next;
    delete head_;
    head_ = next;
  }
  tail_ = nullptr;
  size_ = 0;
}

char& DoublyLinkedList::Back() {
  if (Empty()) {
    throw std::invalid_argument("index out of bounds");
  }
  return tail_->data;
}

char& DoublyLinkedList::Front() {
  if (Empty()) {
    throw std::invalid_argument("index out of bounds");
  }
  return head_->data;
}

void DoublyLinkedList::PopBack() {
  if (Empty()) {
    throw std::invalid_argument("index out of bounds");
  }
  if (head_ == tail_) {
    delete head_;
    head_ = nullptr;
    tail_ = nullptr;
    size_--;
    return;
  }

  Node* prev_nod = tail_->prev;
  prev_nod->next = nullptr;
  delete tail_;
  tail_ = prev_nod;
  size_--;
}

void DoublyLinkedList::PopFront() {
  if (Empty()) {
    throw std::invalid_argument("index out of bounds");
  }

  if (head_ == tail_) {
    delete head_;
    head_ = nullptr;
    tail_ = nullptr;
    size_--;
    return;
  }

  Node* next_nod = head_->next;
  next_nod->prev = nullptr;
  delete head_;
  head_ = next_nod;
  size_--;
}

void DoublyLinkedList::PushBack(char val) {
  if (tail_ == nullptr) {
    head_ = tail_ = new Node(val);
  } else {
    Node* tmp = new Node(val);
    tail_->next = tmp;
    tmp->prev = tail_;
    tail_ = tmp;
  }
  size_++;
}

void DoublyLinkedList::PushFront(char val) {
  if (head_ == nullptr) {
    head_ = tail_ = new Node(val);
  } else {
    Node* tmp = new Node(val);
    head_->prev = tmp;
    tmp->next = head_;
    head_ = tmp;
  }
  size_++;
}

void DoublyLinkedList::InsertAt(size_t idx, char val) {
  if (idx > size_ || idx < 0) {
    throw std::invalid_argument("index out of bounds");
  }

  if (idx == 0) {
    PushFront(val);
  } else if (idx == size_) {
    PushBack(val);
  } else {
    Node* current = head_;
    for (size_t i = 0; i < idx - 1; i++) {
      current = current->next;
    }
    Node* current_next = current->next;
    Node* add_node = new Node(val);

    add_node->next = current_next;
    add_node->prev = current;

    current->next = add_node;
    current_next->prev = add_node;
    size_++;
  }
}

void DoublyLinkedList::EraseAt(size_t idx) {
  if (idx >= size_ || idx < 0) {
    throw std::invalid_argument("index out of bounds");
  }
  if (idx == 0) {
    PopFront();
  } else if (idx == size_ - 1) {
    PopBack();
  } else {
    Node* current = head_;
    for (size_t i = 0; i < idx; i++) {
      current = current->next;
    }
    Node* current_prev = current->prev;
    Node* current_next = current->next;

    current_prev->next = current_next;
    current_next->prev = current_prev;
    delete current;
    size_--;
  }
}

char& DoublyLinkedList::Find(char val) {
  Node* current = head_;
  while (current != nullptr) {
    if (current->data == val) {
      return current->data;
    }
    current = current->next;
  }
  throw std::invalid_argument("index out of bounds");
}
// Functions provided to you
ostream& operator<<(ostream& os, const DoublyLinkedList& ll) {
  constexpr unsigned int kWidth = 16;
  os << "Doubly Linked List" << endl;
  os << "Head: " << ll.head_ << "\t Tail: " << ll.tail_ << endl;
  os << "Size: " << ll.size_ << endl;
  if (ll.head_ == nullptr) return (os << "Empty" << endl);
  const Node* curr = ll.head_;
  os << "Nodes (accessible from head to tail):" << endl << endl;
  os << setw(kWidth) << setfill(' ') << ' ' << ' ' << Center("prev", kWidth - 1)
     << ' ' << Center("data", kWidth - 1) << ' ' << Center("next", kWidth - 1)
     << endl;
  while (curr != nullptr) {
    ostringstream oss;
    oss << (curr->prev);
    string prev = oss.str();
    oss.str("");
    oss << (curr->next);
    string next = oss.str();
    oss.str("");
    oss << (curr->data);
    string data = oss.str();
    oss.str("");
    oss << curr;
    string address = oss.str();
    os << setw(kWidth) << setfill(' ') << ' ' << '.' << setw(kWidth)
       << setfill('-') << '.' << setw(kWidth) << '.' << setw(kWidth) << '.'
       << endl;
    os << setw(kWidth) << setfill(' ') << Center(address, kWidth - 1) << '|'
       << setw(kWidth - 1) << setfill(' ') << Center(prev, kWidth - 1) << '|'
       << setw(kWidth - 1) << Center(data, kWidth - 1) << '|'
       << setw(kWidth - 1) << Center(next, kWidth - 1) << '|' << endl;
    os << setw(kWidth) << setfill(' ') << ' ' << '\'' << setw(kWidth)
       << setfill('-') << '\'' << setw(kWidth) << '\'' << setw(kWidth) << '\''
       << endl;
    os << endl;
    curr = curr->next;
  }
  return os;
}

std::string Center(const std::string& str, decltype(str.length()) col_width) {
  // quick and easy (but error-prone) implementation
  decltype(str.length()) padl = (col_width - str.length()) / 2;
  decltype(str.length()) padr = (col_width - str.length()) - padl;
  string strf = string(padl, ' ') + str + string(padr, ' ');
  return strf;
}