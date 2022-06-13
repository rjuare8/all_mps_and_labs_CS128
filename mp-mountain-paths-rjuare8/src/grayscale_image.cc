#include "grayscale_image.hpp"

#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

#include "color.hpp"

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  image_ = {};
  width_ = dataset.Width();
  height_ = dataset.Height();

  for (size_t i = 0; i < dataset.Height(); i++) {
    std::vector<Color> row_colors = {};
    for (size_t j = 0; j < dataset.Width(); j++) {
      int elev_val = dataset.GetData().at(i).at(j);
      double shade_of_gray = 0;
      if (dataset.MaxEle() == dataset.MinEle()) {
        shade_of_gray = 0;
      } else {
        double operation = (elev_val - dataset.MinEle()) /
                           (double)(dataset.MaxEle() - dataset.MinEle());
        // std::cout << operation << std::endl;
        shade_of_gray = std::round(operation * kMaxColorValue);
      }
      Color color((int)shade_of_gray, (int)shade_of_gray, (int)shade_of_gray);
      row_colors.push_back(color);
    }
    image_.push_back(row_colors);
  }
}

GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height) {
  ElevationDataset dataset(filename, width, height);
  image_ = {};
  width_ = dataset.Width();
  height_ = dataset.Height();

  for (size_t i = 0; i < dataset.Height(); i++) {
    std::vector<Color> row_colors = {};
    for (size_t j = 0; j < dataset.Width(); j++) {
      int elev_val = dataset.GetData().at(i).at(j);
      double shade_of_gray = 0;
      if (dataset.MaxEle() == dataset.MinEle()) {
        shade_of_gray = 0;
      } else {
        double operation = (elev_val - dataset.MinEle()) /
                           (double)(dataset.MaxEle() - dataset.MinEle());
        std::cout << operation << std::endl;
        shade_of_gray = std::round(operation * kMaxColorValue);
      }
      Color color((int)shade_of_gray, (int)shade_of_gray, (int)shade_of_gray);
      row_colors.push_back(color);
    }
    image_.push_back(row_colors);
  }
}

size_t GrayscaleImage::Width() const { return width_; }

size_t GrayscaleImage::Height() const { return height_; }

unsigned int GrayscaleImage::MaxColorValue() const { return kMaxColorValue; }

const Color& GrayscaleImage::ColorAt(int row, int col) const {
  return image_.at(row).at(col);
}

const std::vector<std::vector<Color>>& GrayscaleImage::GetImage() const {
  return image_;
}

void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream ofs(name);
  ofs << "P3" << std::endl;
  ofs << width_ << " " << height_ << std::endl;
  ofs << kMaxColorValue << std::endl;

  for (size_t row = 0; row < height_; row++) {
    for (size_t col = 0; col < width_; col++) {
      int green = image_.at(row).at(col).Green();
      int red = image_.at(row).at(col).Red();
      int blue = image_.at(row).at(col).Blue();
      ofs << red << " " << green << " " << blue << " ";
    }
    ofs << std::endl;
  }
  ofs << std::endl;
}
