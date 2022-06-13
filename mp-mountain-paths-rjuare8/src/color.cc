#include "color.hpp"

#include <stdexcept>

const int kMaxRGB = 255;

Color::Color(int r, int g, int b): red_(r), green_(g), blue_(b) {
  if (!(0 <= red_ && red_ <= kMaxRGB && 0 <= green_ && green_ <= kMaxRGB &&
        0 <= blue_ && blue_ <= kMaxRGB)) {
    throw std::invalid_argument("color out of range");
  }
  // need to ensure valid color has been constructed...
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}