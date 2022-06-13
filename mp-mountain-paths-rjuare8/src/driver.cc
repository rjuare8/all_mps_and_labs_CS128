#include <iostream>

#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"

int main(int argc, char* argv[]) {
  int lol = argc;
  lol++;
  int width = 51;
  int height = 55;

  ElevationDataset Test(argv[1], width, height);

  GrayscaleImage gray_image(Test);

  PathImage path_image(gray_image, Test);
}