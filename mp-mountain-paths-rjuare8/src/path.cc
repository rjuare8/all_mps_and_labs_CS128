#include "path.hpp"

Path::Path(size_t length, size_t starting_row) {
  length_ = length;

  std::vector<size_t> path(length_);
  path_ = path;

  starting_row_ = starting_row;

  ele_change_ = 0;
}

size_t Path::Length() const { return length_; }

size_t Path::StartingRow() const { return starting_row_; }

unsigned int Path::EleChange() const { return ele_change_; }

void Path::IncEleChange(unsigned int value) { ele_change_ += value; }

const std::vector<size_t>& Path::GetPath() const { return path_; }

void Path::SetLoc(size_t col, size_t row) { path_.at(col) = row; }
