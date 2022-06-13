#include "seam_carver.hpp"

// clang-format off

// implement the rest of SeamCarver's functions here

// given functions below, DO NOT MODIFY

SeamCarver::SeamCarver(const ImagePPM& image): image_(image) {
  height_ = image.GetHeight();
  width_ = image.GetWidth();
}

void SeamCarver::SetImage(const ImagePPM& image) {
  image_ = image;
  width_ = image.GetWidth();
  height_ = image.GetHeight();
}

const ImagePPM& SeamCarver::GetImage() const { return image_; }

int SeamCarver::GetHeight() const { return height_; }

int SeamCarver::GetWidth() const { return width_; }

int SeamCarver::GetEnergy(int row, int col) const {
  int energy = 0;
  if (row == 0) {
    energy = EnergyFirstRow(row, col);
  } else if (row == height_ - 1) {
    energy = EnergyLastRow(row, col);
  } else if (col == 0) {
    energy = EnergyFirstCol(row, col);
  } else if (col == width_ - 1) {
    energy = EnergyLastCol(row, col);
  } else {
    energy = EnergyNormalCase(row, col);
  }

  return energy;
}

int* SeamCarver::GetHorizontalSeam() const { 
  int** energy_arr = new int*[height_]; int** min_arr = new int*[height_];

  for (int row = 0; row < height_; row++) {
    energy_arr[row] = new int[width_]; min_arr[row] = new int[width_];
  }

  for (int col = 0; col < width_; col++) {
    for (int row = 0; row < height_; row++) {
      energy_arr[row][col] = GetEnergy(row, col);
      if (col == width_ - 1) {
        min_arr[row][col] = GetEnergy(row, col);
      }
    }
  }
  for (int col = width_ - 2; col >= 0; col--) {
    for (int row = 0; row < height_; row++) {
      int left = INT32_MAX; int mid = INT32_MAX; int right = INT32_MAX;
      if (row == 0) {
        right = min_arr[row + 1][col + 1]; mid = min_arr[row][col + 1];

      } else if (row == height_ - 1) {
        left = min_arr[row - 1][col + 1]; mid = min_arr[row][col + 1];

      } else {
        right = min_arr[row + 1][col + 1]; mid = min_arr[row][col + 1]; left = min_arr[row - 1][col + 1];
      }
      int min = std::min(left, std::min(mid, right));
      min_arr[row][col] = energy_arr[row][col] + min;
    }
  }

  int* hor_seam = TieBrakerHorizontal(min_arr);

  for (int row = 0; row < height_; row++) {
    delete[] min_arr[row]; delete[] energy_arr[row];
  }
  delete[] min_arr; min_arr = nullptr; delete[] energy_arr; energy_arr = nullptr;

  return hor_seam;
}

int* SeamCarver::TieBrakerHorizontal(int**& min_array) const {
  // get row of lowest value in the first col
  int* hor_seam = new int[width_];
  int col_idx = 0; int row_idx = 0;

  int lowest_val = INT32_MAX;
  for (int row = 0; row < height_; row++) {
    if (min_array[row][0] < lowest_val) {
      lowest_val = min_array[row_idx][0];
      row_idx = row;
    }
  }
  hor_seam[0] = row_idx; col_idx++;

  for (int col = 0; col <= width_ - 2; col++) {
    int right = INT32_MAX; int mid = INT32_MAX; int left = INT32_MAX;
    if (row_idx == 0) {
      mid = min_array[row_idx][col + 1]; right = min_array[row_idx + 1][col + 1];
      if (right < mid) {
        row_idx++;
      }
    } else if (row_idx == height_ - 1) {
      left = min_array[row_idx - 1][col + 1]; mid = min_array[row_idx][col + 1];
      if (left < mid) {
        row_idx--;
      }
    } else {
      right = min_array[row_idx + 1][col + 1]; mid = min_array[row_idx][col + 1]; left = min_array[row_idx - 1][col + 1];
      if ((left < mid && left < right) ||
          (left == right && left < mid)) {
        row_idx--;
      } else if (right < mid && right < left) {
        row_idx++;
      }
    }
    hor_seam[col_idx] = row_idx;
    col_idx++;
  }

  return hor_seam;
}

int* SeamCarver::GetVerticalSeam() const {
  int** energy_arr = new int*[height_]; int** min_arr = new int*[height_];

  for (int row = 0; row < height_; row++) {
    energy_arr[row] = new int[width_]; min_arr[row] = new int[width_];
  }

  for (int row = 0; row < height_; row++) {
    for (int col = 0; col < width_; col++) {
      energy_arr[row][col] = GetEnergy(row, col);
      if (row == height_ - 1) {
        min_arr[row][col] = GetEnergy(row, col);
      }
    }
  }
  for (int row = height_ - 2; row >= 0; row--) {
    for (int col = 0; col < width_; col++) {
      int left = INT32_MAX; int mid = INT32_MAX; int right = INT32_MAX;
      if (col == 0) {
        right = min_arr[row + 1][col + 1]; mid = min_arr[row + 1][col];

      } else if (col == width_ - 1) {
        left = min_arr[row + 1][col - 1]; mid = min_arr[row + 1][col];

      } else {
        left = min_arr[row + 1][col - 1]; mid = min_arr[row + 1][col]; right = min_arr[row + 1][col + 1];
      }
      int min = std::min(std::min(left, mid), right);
      min_arr[row][col] = energy_arr[row][col] + min;
    }
  }

  int* vert_seam = TieBrakerVertical(min_arr);

  for (int row = 0; row < height_; row++) {
    delete[] min_arr[row]; delete energy_arr[row];
  }
  delete[] min_arr; min_arr = nullptr; delete[] energy_arr; energy_arr = nullptr;

  return vert_seam;
}

int* SeamCarver::TieBrakerVertical(int**& min_array) const {
  // get column of lowest value in the first row
  int* ver_seam = new int[height_];
  int col_idx = 0; int row_idx = 0;

  int lowest_val = INT32_MAX;
  for (int col = 0; col < width_; col++) {
    if (min_array[0][col] < lowest_val) {
      col_idx = col;
      lowest_val = min_array[0][col_idx];
    }
  }
  ver_seam[0] = col_idx; row_idx++;

  for (int row = 0; row <= height_ - 2; row++) {
    int down_l_val = INT32_MAX; int down_val = INT32_MAX; int down_r_val = INT32_MAX;
    if (col_idx == 0) {
      down_val = min_array[row + 1][col_idx]; down_r_val = min_array[row + 1][col_idx + 1];
      if (down_r_val < down_val) {
        col_idx++;
      }
    } else if (col_idx == width_ - 1) {
      down_l_val = min_array[row + 1][col_idx - 1]; down_val = min_array[row + 1][col_idx];
      if (down_l_val < down_val) {
        col_idx--;
      }
    } else {
      down_l_val = min_array[row + 1][col_idx - 1]; down_val = min_array[row + 1][col_idx]; down_r_val = min_array[row + 1][col_idx + 1];
      if ((down_l_val < down_val && down_l_val < down_r_val) ||
          (down_l_val == down_r_val && down_l_val < down_val)) {
        col_idx--;
      } else if (down_r_val < down_val && down_r_val < down_l_val) {
        col_idx++;
      }
    }
    ver_seam[row_idx] = col_idx;
    row_idx++;
  }

  return ver_seam;
}

void SeamCarver::RemoveHorizontalSeam() { 
  auto** new_arr = new Pixel*[height_ - 1];
  for (int row = 0; row < height_ - 1; row++) {
    new_arr[row] = new Pixel[width_];
  }
  int* hori_seam = GetHorizontalSeam();
  for (int col = 0; col < width_; col++) {
    int row_idx = 0;
    for (int row = 0; row < height_; row++) {
      if (row != hori_seam[col]) {
        new_arr[row_idx][col] = image_.GetPixel(row, col);
        row_idx++;
      }
    }
  }

  height_ = height_ - 1;
  ImagePPM tmp_image(new_arr, height_, width_, image_.GetMaxColorValue());
  image_ = tmp_image;

  delete[] hori_seam; hori_seam = nullptr; 
}

void SeamCarver::RemoveVerticalSeam() { 
  auto** new_arr = new Pixel*[height_];
  for (int row = 0; row < height_; row++) {
    new_arr[row] = new Pixel[width_ - 1];
  }
  int* vert_seam = GetVerticalSeam();

  
  for (int row = 0; row < height_; row++) {
    int col_idx = 0;
    for (int col = 0; col < width_; col++) {
      if (col != vert_seam[row]) {
        new_arr[row][col_idx] = image_.GetPixel(row, col);
        col_idx++;
      }
    }
  }
  
  width_ = width_ - 1;
  ImagePPM tmp_image(new_arr, height_, width_, image_.GetMaxColorValue());
  image_ = tmp_image;

  delete[] vert_seam; vert_seam = nullptr;
}

int SeamCarver::EnergyFirstRow(int row, int col) const {
  Pixel left_pixel(0, 0, 0);
  Pixel right_pixel(0, 0, 0);
  Pixel up_pixel(0, 0, 0);
  Pixel down_pixel(0, 0, 0);
  if (col == 0) {
    left_pixel = image_.GetPixel(0, width_ - 1);
    right_pixel = image_.GetPixel(row, col + 1);
    up_pixel = image_.GetPixel(height_ - 1, 0);
    down_pixel = image_.GetPixel(row + 1, 0);

  } else if (col == width_ - 1) {
    left_pixel = image_.GetPixel(row, col - 1);
    right_pixel = image_.GetPixel(0, 0);
    up_pixel = image_.GetPixel(height_ - 1, width_ - 1);
    down_pixel = image_.GetPixel(row + 1, col);

  } else {
    left_pixel = image_.GetPixel(row, col - 1);
    right_pixel = image_.GetPixel(row, col + 1);
    up_pixel = image_.GetPixel(height_ - 1, col);
    down_pixel = image_.GetPixel(row + 1, col);
  }

  int red_col = ((left_pixel.GetRed() - right_pixel.GetRed()) *
                 (left_pixel.GetRed() - right_pixel.GetRed()));
  int green_col = ((left_pixel.GetGreen() - right_pixel.GetGreen()) *
                   (left_pixel.GetGreen() - right_pixel.GetGreen()));
  int blue_col = ((left_pixel.GetBlue() - right_pixel.GetBlue()) *
                  (left_pixel.GetBlue() - right_pixel.GetBlue()));
  int red_row = ((up_pixel.GetRed() - down_pixel.GetRed()) *
                 (up_pixel.GetRed() - down_pixel.GetRed()));
  int green_row = ((up_pixel.GetGreen() - down_pixel.GetGreen()) *
                   (up_pixel.GetGreen() - down_pixel.GetGreen()));
  int blue_row = ((up_pixel.GetBlue() - down_pixel.GetBlue()) *
                  (up_pixel.GetBlue() - down_pixel.GetBlue()));
  int diff_col = red_col + green_col + blue_col;
  int diff_row = red_row + green_row + blue_row;

  return diff_col + diff_row;
}

int SeamCarver::EnergyLastRow(int row, int col) const {
  Pixel left_pixel(0, 0, 0);
  Pixel right_pixel(0, 0, 0);
  Pixel up_pixel(0, 0, 0);
  Pixel down_pixel(0, 0, 0);
  if (col == 0) {
    left_pixel = image_.GetPixel(height_ - 1, width_ - 1);
    right_pixel = image_.GetPixel(row, col + 1);
    up_pixel = image_.GetPixel(row - 1, col);
    down_pixel = image_.GetPixel(0, 0);

  } else if (col == width_ - 1) {
    left_pixel = image_.GetPixel(row, col - 1);
    right_pixel = image_.GetPixel(height_ - 1, 0);
    up_pixel = image_.GetPixel(row - 1, col);
    down_pixel = image_.GetPixel(0, width_ - 1);

  } else {
    left_pixel = image_.GetPixel(row, col - 1);
    right_pixel = image_.GetPixel(row, col + 1);
    up_pixel = image_.GetPixel(row - 1, col);
    down_pixel = image_.GetPixel(0, col);
  }

  int red_col = ((left_pixel.GetRed() - right_pixel.GetRed()) *
                 (left_pixel.GetRed() - right_pixel.GetRed()));
  int green_col = ((left_pixel.GetGreen() - right_pixel.GetGreen()) *
                   (left_pixel.GetGreen() - right_pixel.GetGreen()));
  int blue_col = ((left_pixel.GetBlue() - right_pixel.GetBlue()) *
                  (left_pixel.GetBlue() - right_pixel.GetBlue()));
  int red_row = ((up_pixel.GetRed() - down_pixel.GetRed()) *
                 (up_pixel.GetRed() - down_pixel.GetRed()));
  int green_row = ((up_pixel.GetGreen() - down_pixel.GetGreen()) *
                   (up_pixel.GetGreen() - down_pixel.GetGreen()));
  int blue_row = ((up_pixel.GetBlue() - down_pixel.GetBlue()) *
                  (up_pixel.GetBlue() - down_pixel.GetBlue()));
  int diff_col = red_col + green_col + blue_col;
  int diff_row = red_row + green_row + blue_row;

  return diff_col + diff_row;
}

int SeamCarver::EnergyFirstCol(int row, int col) const {
  Pixel left_pixel = image_.GetPixel(row, width_ - 1);
  Pixel right_pixel = image_.GetPixel(row, col + 1);
  Pixel up_pixel = image_.GetPixel(row - 1, col);
  Pixel down_pixel = image_.GetPixel(row + 1, col);

  int red_col = ((left_pixel.GetRed() - right_pixel.GetRed()) *
                 (left_pixel.GetRed() - right_pixel.GetRed()));
  int green_col = ((left_pixel.GetGreen() - right_pixel.GetGreen()) *
                   (left_pixel.GetGreen() - right_pixel.GetGreen()));
  int blue_col = ((left_pixel.GetBlue() - right_pixel.GetBlue()) *
                  (left_pixel.GetBlue() - right_pixel.GetBlue()));
  int red_row = ((up_pixel.GetRed() - down_pixel.GetRed()) *
                 (up_pixel.GetRed() - down_pixel.GetRed()));
  int green_row = ((up_pixel.GetGreen() - down_pixel.GetGreen()) *
                   (up_pixel.GetGreen() - down_pixel.GetGreen()));
  int blue_row = ((up_pixel.GetBlue() - down_pixel.GetBlue()) *
                  (up_pixel.GetBlue() - down_pixel.GetBlue()));
  int diff_col = red_col + green_col + blue_col;
  int diff_row = red_row + green_row + blue_row;

  return diff_col + diff_row;
}

int SeamCarver::EnergyLastCol(int row, int col) const {
  Pixel left_pixel = image_.GetPixel(row, col - 1);
  Pixel right_pixel = image_.GetPixel(row, 0);
  Pixel up_pixel = image_.GetPixel(row - 1, col);
  Pixel down_pixel = image_.GetPixel(row + 1, col);

  int red_col = ((left_pixel.GetRed() - right_pixel.GetRed()) *
                 (left_pixel.GetRed() - right_pixel.GetRed()));
  int green_col = ((left_pixel.GetGreen() - right_pixel.GetGreen()) *
                   (left_pixel.GetGreen() - right_pixel.GetGreen()));
  int blue_col = ((left_pixel.GetBlue() - right_pixel.GetBlue()) *
                  (left_pixel.GetBlue() - right_pixel.GetBlue()));
  int red_row = ((up_pixel.GetRed() - down_pixel.GetRed()) *
                 (up_pixel.GetRed() - down_pixel.GetRed()));
  int green_row = ((up_pixel.GetGreen() - down_pixel.GetGreen()) *
                   (up_pixel.GetGreen() - down_pixel.GetGreen()));
  int blue_row = ((up_pixel.GetBlue() - down_pixel.GetBlue()) *
                  (up_pixel.GetBlue() - down_pixel.GetBlue()));
  int diff_col = red_col + green_col + blue_col;
  int diff_row = red_row + green_row + blue_row;

  return diff_col + diff_row;
}

int SeamCarver::EnergyNormalCase(int row, int col) const {
  Pixel left_pixel = image_.GetPixel(row, col - 1);
  Pixel right_pixel = image_.GetPixel(row, col + 1);
  Pixel up_pixel = image_.GetPixel(row - 1, col);
  Pixel down_pixel = image_.GetPixel(row + 1, col);

  int red_col = ((left_pixel.GetRed() - right_pixel.GetRed()) *
                 (left_pixel.GetRed() - right_pixel.GetRed()));
  int green_col = ((left_pixel.GetGreen() - right_pixel.GetGreen()) *
                   (left_pixel.GetGreen() - right_pixel.GetGreen()));
  int blue_col = ((left_pixel.GetBlue() - right_pixel.GetBlue()) *
                  (left_pixel.GetBlue() - right_pixel.GetBlue()));
  int red_row = ((up_pixel.GetRed() - down_pixel.GetRed()) *
                 (up_pixel.GetRed() - down_pixel.GetRed()));
  int green_row = ((up_pixel.GetGreen() - down_pixel.GetGreen()) *
                   (up_pixel.GetGreen() - down_pixel.GetGreen()));
  int blue_row = ((up_pixel.GetBlue() - down_pixel.GetBlue()) *
                  (up_pixel.GetBlue() - down_pixel.GetBlue()));
  int diff_col = red_col + green_col + blue_col;
  int diff_row = red_row + green_row + blue_row;

  return diff_col + diff_row;
}
