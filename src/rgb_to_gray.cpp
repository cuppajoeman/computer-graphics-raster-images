#include "rgb_to_gray.h"

void rgb_to_gray(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  std::vector<unsigned char> & gray)
{
  gray.resize(height*width);

  unsigned int rgb_pixel_idx = 0;
  for (int i = 0;  i < rgb.size(); i += 3) {
    unsigned char red = rgb[i];
    unsigned char green = rgb[i + 1];
    unsigned char blue = rgb[i + 2];
    // don't operate on alpha
    gray[i / 3] = 0.2126 * red + 0.7152 * green + 0.0722 * blue;
  }
}
