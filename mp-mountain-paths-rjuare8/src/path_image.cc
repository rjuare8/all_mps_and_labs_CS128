#include "path_image.hpp"

#include <cmath>
#include <fstream>
#include <iostream>

#include "path.hpp"

const int kGreenR = 31;
const int kGreenG = 253;
const int kGreenB = 13;

const int kRedR = 252;
const int kRedG = 25;
const int kRedB = 63;

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset) {
  width_ = image.GetImage().at(0).size();
  height_ = image.GetImage().size();

  paths_ = {};
  path_image_ = {};

  bool first_elev = true;
  std::vector<size_t> lowest_path = {};
  size_t row_less_res = 0;
  int lowest_res = 0;

  for (size_t i = 0; i < height_; i++) {
    Path path(width_, i);
    path.SetLoc(0, i);
    int ele_change = 0;

    size_t row = i;
    // std::cout << "test 1:" << i << std::endl;
    for (size_t col = 1; col < width_; col++) {
      // if the row is in a higher position, the we only consider the forward
      // and southeast values

      if (row == 0) {
        // std::cout << "test 3" << std::endl;
        int cha_fwd =
            abs(dataset.DatumAt(row, col - 1) - dataset.DatumAt(row, col));
        int cha_down =
            abs(dataset.DatumAt(row, col - 1) - dataset.DatumAt(row + 1, col));
        if ((cha_fwd == cha_down) || (cha_fwd < cha_down)) {
          path.SetLoc(col, row);
          ele_change += cha_fwd;
        } else {
          path.SetLoc(col, row + 1);
          ele_change += cha_down;
          row++;
        }
      } else if (row ==
                 height_ - 1) {  // if the row is lower that the lowest
                                 // position, the only directions that we
                                 // consider is the forward and northeast values
        // std::cout << "test 4" << std::endl;
        int cha_up =
            abs(dataset.DatumAt(row, col - 1) - dataset.DatumAt(row - 1, col));
        int cha_fwd =
            abs(dataset.DatumAt(row, col - 1) - dataset.DatumAt(row, col));
        if ((cha_fwd == cha_up) || (cha_fwd < cha_up)) {
          path.SetLoc(col, row);
          ele_change += cha_fwd;
        } else {
          path.SetLoc(col, row - 1);
          ele_change += cha_up;
          row--;
        }
      } else {
        // std::cout << "test 5" << std::endl;
        int cha_up =
            abs(dataset.DatumAt(row, col - 1) - dataset.DatumAt(row - 1, col));
        int cha_fwd =
            abs(dataset.DatumAt(row, col - 1) - dataset.DatumAt(row, col));
        int cha_down =
            abs(dataset.DatumAt(row, col - 1) - dataset.DatumAt(row + 1, col));
        if ((cha_down == cha_up && cha_down == cha_fwd) ||
            (cha_fwd == cha_up && cha_fwd < cha_down) ||
            (cha_fwd == cha_down && cha_fwd < cha_up) ||
            (cha_fwd < cha_up && cha_fwd < cha_down)) {
          path.SetLoc(col, row);
          ele_change += cha_fwd;
        } else if ((cha_up == cha_down && cha_up < cha_fwd) ||
                   (cha_down < cha_fwd && cha_down < cha_up)) {
          path.SetLoc(col, row + 1);
          ele_change += cha_up;
          row++;

        } else if (cha_up < cha_fwd && cha_up < cha_down) {
          path.SetLoc(col, row - 1);
          ele_change += cha_up;
          row--;
        }
      }
    }
    if (first_elev) {
      lowest_res = ele_change;
      std::cout << "test lowest val " << lowest_res << std::endl;
      first_elev = false;
    }
    std::cout << i << std::endl;
    if (ele_change < lowest_res) {
      row_less_res = i;
      lowest_res = ele_change;
      lowest_path = path.GetPath();
      std::cout << "lowest path is in " << row_less_res
                << " and the elevation change is " << lowest_res << std::endl;
    }

    path.IncEleChange(ele_change);
    paths_.push_back(path);
    // std::cout << "test pushback complete" << std::endl;
  }

  for (size_t i = 0; i < height_; i++) {
    std::vector<Color> row_colors = {};
    for (size_t col = 0; col < width_; col++) {
      row_colors.push_back((image.ColorAt(i, col)));
    }
    path_image_.push_back(row_colors);
  }

  for (size_t i = 0; i < height_; i++) {
    for (size_t col = 0; col < width_; col++) {
      Color red(kRedR, kRedG, kRedB);
      size_t row_red = paths_.at(i).GetPath().at(col);
      path_image_.at(row_red).at(col) = red;
    }
  }

  for (size_t col = 0; col < width_; col++) {
    Color green(kGreenR, kGreenG, kGreenB);
    size_t row_green = paths_.at(row_less_res).GetPath().at(col);
    path_image_.at(row_green).at(col) = green;
  }

  for (size_t i = 0; i < height_; i++) {
    std::cout << "The path starting row is: " << paths_.at(i).StartingRow()
              << " and the elevation change is " << paths_.at(i).EleChange()
              << std::endl;
  }

  for (size_t row = 0; row < height_; row++) {
    for (size_t col = 0; col < width_; col++) {
      int green = path_image_.at(row).at(col).Green();
      int red = path_image_.at(row).at(col).Red();
      int blue = path_image_.at(row).at(col).Blue();
      std::cout << red << " " << green << " " << blue << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

size_t PathImage::Width() const { return width_; }

size_t PathImage::Height() const { return height_; }

unsigned int PathImage::MaxColorValue() const { return kMaxColorValue; }

const std::vector<Path>& PathImage::Paths() const { return paths_; }

const std::vector<std::vector<Color>>& PathImage::GetPathImage() const {
  return path_image_;
}

void PathImage::ToPpm(const std::string& name) const {
  std::ofstream ofs(name);
  ofs << "P3" << std::endl;
  ofs << width_ << " " << height_ << std::endl;
  ofs << kMaxColorValue << std::endl;

  for (size_t row = 0; row < height_; row++) {
    for (size_t col = 0; col < width_; col++) {
      int green = path_image_.at(row).at(col).Green();
      int red = path_image_.at(row).at(col).Red();
      int blue = path_image_.at(row).at(col).Blue();
      ofs << red << " " << green << " " << blue << " ";
    }
    ofs << std::endl;
  }
  ofs << std::endl;
}
