#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();

  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);
  void ModifyStrand(DNAstrand& to_splice_in, Node*& node_ini, Node*& node_end);

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

#endif