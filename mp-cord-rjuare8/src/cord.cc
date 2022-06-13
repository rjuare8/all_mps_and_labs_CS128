// clang-format off

#include "cord.hpp"




#include "cord-utilities.hpp"

Cord::Cord(const std::string& dat) {
  data_ = dat;
  length_ = dat.length();
}

Cord::Cord(const std::shared_ptr<Cord>& left_cord,
           const std::shared_ptr<Cord>& right_cord) {
  length_ = left_cord->length_ + right_cord->length_;
  left_ = left_cord;
  right_ = right_cord;
  // TODO
}

size_t Cord::Length() const { return length_; }

std::shared_ptr<Cord> Cord::GetLeft() const { return left_; }

std::shared_ptr<Cord> Cord::GetRight() const { return right_; }

const std::string& Cord::GetData() const { return data_; }

std::string Cord::ToString() const {
  std::string to_return;

  ToStringRecursive(to_return, *this);

  return to_return;
}

void Cord::ToStringRecursive(std::string& string, const Cord& cord) const {
  if (cord.GetLeft() != nullptr) {
    ToStringRecursive(string, *cord.GetLeft());
  }
  if (cord.GetRight() != nullptr) {
    ToStringRecursive(string, *cord.GetRight());
  }

  string += cord.data_;
}

std::shared_ptr<Cord> Cord::SubString(size_t lower_idx, size_t upper_idx) {
  if (lower_idx == 0 && upper_idx == this->Length()) return this->shared_from_this();
  std::shared_ptr<Cord> left_cord = nullptr;
  std::shared_ptr<Cord> right_cord = nullptr;
  if (this->left_ != nullptr) {
    size_t left_length = this->GetLeft()->Length();
    if (lower_idx < left_length) {
      size_t new_upper = upper_idx;
      if (upper_idx > left_length) new_upper = left_length;
      left_cord = this->left_->SubString(lower_idx, new_upper);
    }
  }
  if (this->right_ != nullptr) {
    if (this->GetLeft()->Length() < upper_idx) {
      size_t new_lower = lower_idx;
      if (lower_idx < this->GetLeft()->Length()) new_lower = this->GetLeft()->Length();
      
      new_lower -= this->GetLeft()->Length();
      size_t new_upper = upper_idx - this->GetLeft()->Length();
      
      right_cord = this->right_->SubString(new_lower, new_upper);
    }
  }
  if (this->IsLeafNode()) {
    std::string cord_string;
    
    for (size_t i = lower_idx; i < upper_idx; i++) {
      cord_string += this->data_.at(i);
    }
    return std::make_shared<Cord>(cord_string);
  }
  std::shared_ptr<Cord> concat_cord = ConcatCords(left_cord, right_cord);
  return concat_cord;
}

void Cord::CheckCords(std::map<std::string, std::shared_ptr<Cord>>& visited,
                  std::shared_ptr<Cord>& cord) const {
  if (visited.find(cord->ToString()) == visited.end()) {
    visited.insert({cord->ToString(), cord});
    
  } else {

    cord = visited.at(cord->ToString());
  }

  

  if (cord->GetLeft() != nullptr && cord->GetRight() != nullptr) {
    CheckCords(visited, cord->left_);
    CheckCords(visited, cord->right_);
  }

  
                  
}

char Cord::At(size_t idx) const {
  if (idx >= length_) throw std::invalid_argument("index out of bounds");

  char to_return = '$';
  AtRecursive(idx, *this, to_return);

  return to_return;
}

void Cord::AtRecursive(size_t& idx, const Cord& cord, char& val) const {
  if (cord.GetLeft() != nullptr) {
    AtRecursive(idx, *cord.GetLeft(), val);
  }
  if (cord.GetRight() != nullptr) {
    AtRecursive(idx, *cord.GetRight(), val);
  }

  if (cord.data_.length() != 0) {
    if (idx < cord.length_ && val == '$') {
      val = cord.data_.at(idx);
    } else {
      idx -= cord.length_;
    }
  }
}

bool Cord::IsValidCord() const {
  return !(!this->IsInternalNode() && !this->IsLeafNode());
}

bool Cord::IsInternalNode() const {
  return (this->data_.length() == 0 &&
          (this->left_ != nullptr && this->right_ != nullptr)) &&
         (this->length_ == this->right_->length_ + this->left_->length_);
}

bool Cord::IsLeafNode() const {
  return this->data_.length() > 0 && this->right_ == nullptr &&
         this->left_ == nullptr;
}
