// clang-format off

#include "dna_strand.hpp"

#include <stdexcept>

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  if (pattern[0] == '\0' || to_splice_in.head_ == nullptr || &to_splice_in == this) return;
  //stores the beginning and ending nodes that have the pattern 
  Node* current = head_; int idx_word = 0; Node* node_ini = nullptr; Node* node_end = nullptr; Node* tmp_node_ini = nullptr; bool pat_fou = false;
  while (current != nullptr) {
    if (current->data == pattern[idx_word]) {
      if (idx_word == 0) {
        tmp_node_ini = current;
      } 
      if (pattern[idx_word + 1] == '\0') {
        node_ini = tmp_node_ini; node_end = current; idx_word = 0; pat_fou = true;
      } else {
        idx_word++;
      }
    } else {
      idx_word = 0;
      if (current->data == pattern[idx_word]) {
        if (idx_word == 0) {
          tmp_node_ini = current;
        } 
        if (pattern[idx_word + 1] == '\0') {
          node_ini = tmp_node_ini; node_end = current; idx_word = 0; pat_fou = true;
        } else {
          idx_word++;
        }
      }
    }
    current = current->next; 
  }
  if (!(pat_fou)) throw std::runtime_error("no pattern found");
  //void method begins
  this->ModifyStrand(to_splice_in, node_ini, node_end);
  //void method ends
  while (node_ini != nullptr) {
    Node* next = node_ini->next; delete node_ini; node_ini = next;
  }
  to_splice_in.head_ = nullptr; to_splice_in.tail_ = nullptr; node_ini = nullptr; node_end = nullptr; tmp_node_ini = nullptr;
}

void DNAstrand::ModifyStrand(DNAstrand& to_splice_in, Node*& node_ini, Node*& node_end) {
  Node* current = head_;
  //loop to find the node previous to the one to remove and change the it's next to the one in splice_in
  if (current == node_ini) {
    head_ = to_splice_in.head_;
  } else {
    while (current != node_ini) {
      if (current->next == node_ini) { current->next = to_splice_in.head_; break;}
      current = current->next;
    }
  }
  //change the node tail's next to the node after the pattern. Then change the node at the end of the pattern next to nullptr
  if (node_end == tail_) {
    tail_ = to_splice_in.tail_->next; 
  } else {
    to_splice_in.tail_->next = node_end->next; node_end->next = nullptr;
  }
}

DNAstrand::~DNAstrand() {
  while (head_ != nullptr) {
    Node* next = head_->next;
    delete head_;
    head_ = next;
  }
}


