#include "elevation_dataset.hpp"

#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

ElevationDataset::ElevationDataset(const std::string& filename,
                                   size_t width,
                                   size_t height) {
  width_ = width;
  height_ = height;
  data_ = {};

  std::ifstream ifs(filename);

  int value = 0;
  if (ifs.fail()) {
    throw std::runtime_error("Data not readable");
  }
  while (ifs.good()) {
    ifs >> value;
    if (ifs.fail()) {
      ifs.clear();
      ifs.ignore(1, '\n');
    } else {
      max_ele_ = value;
      min_ele_ = value;
      break;
    }
  }

  std::ifstream ips(filename);

  int val = 0;

  std::vector<int> row_data = {};

  while (ips.good()) {
    ips >> val;
    if (ips.fail()) {
      ips.clear();
      ips.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
      // std::cout << "current value: " << val << std::endl;
      if (val > max_ele_) {
        // std::cout << "max value: " << val << std::endl;
        max_ele_ = val;
      } else if (val < min_ele_) {
        min_ele_ = val;
        // std::cout << "min value: " << val << std::endl;
      }
      row_data.push_back(val);
      if (row_data.size() == width_) {
        data_.push_back(row_data);
        row_data = {};
      }
    }
  }

  if (data_.at(0).size() * data_.size() != width_ * height_) {
    throw std::runtime_error(
        "It does not contain the right amount of data points");
  }
  std::cout << "Absolute min value: " << min_ele_ << std::endl;
  std::cout << "Absolute max value: " << max_ele_ << std::endl;
}

size_t ElevationDataset::Width() const { return width_; }

size_t ElevationDataset::Height() const { return height_; }

int ElevationDataset::MaxEle() const { return max_ele_; }

int ElevationDataset::MinEle() const { return min_ele_; }

int ElevationDataset::DatumAt(size_t row, size_t col) const {
  return data_.at(row).at(col);
}
const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
  return data_;
}