#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"
#include <cmath>

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());

  for (int i = 0; i < width * height; ++i) {
    double r = rgb[i * 3] / 255.0;
    double g = rgb[i * 3 + 1] / 255.0;
    double b = rgb[i * 3 + 2] / 255.0;
    
    double h, s, v;
    rgb_to_hsv(r, g, b, h, s, v);
    
    h = fmod(h + shift, 360.0);
    if (h < 0) h += 360.0;
    
    hsv_to_rgb(h, s, v, r, g, b);
    
    shifted[i * 3] = static_cast<unsigned char>(r * 255);
    shifted[i * 3 + 1] = static_cast<unsigned char>(g * 255);
    shifted[i * 3 + 2] = static_cast<unsigned char>(b * 255);
  }
}
