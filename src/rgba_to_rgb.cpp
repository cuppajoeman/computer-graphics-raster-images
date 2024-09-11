#include "rgba_to_rgb.h"

void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  unsigned int num_pixels_in_rbga_images = rgba.size();
  rgb.resize(height*width*3);

  unsigned int num_pixels_copied = 0;
  unsigned int rgb_pixel_idx = 0;
  for (int i = 0;  i < num_pixels_in_rbga_images; i += 4) {
    unsigned char red = rgba[i];
    unsigned char green = rgba[i + 1];
    unsigned char blue = rgba[i + 2];
    // don't operate on alpha

    rgb[rgb_pixel_idx] = red;
    rgb[rgb_pixel_idx + 1] = green;
    rgb[rgb_pixel_idx + 2] = blue;

    rgb_pixel_idx += 3;
  }
  /*assert(num_pixels_copied == (height * width * 3));*/
}
