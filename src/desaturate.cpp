#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());

  for (int i = 0; i < width * height; ++i) {
    // Properly cast the RGB values to double before dividing by 255.0
    double r = static_cast<double>(rgb[i * 3]) / 255.0;
    double g = static_cast<double>(rgb[i * 3 + 1]) / 255.0;
    double b = static_cast<double>(rgb[i * 3 + 2]) / 255.0;
    
    double h, s, v;
    rgb_to_hsv(r, g, b, h, s, v);
    
    // Apply the desaturation factor to the saturation channel
    s *= (1 - factor);
    
    // Convert back to RGB
    hsv_to_rgb(h, s, v, r, g, b);
    
    // Rescale to 0-255 range and store in desaturated array
    desaturated[i * 3] = static_cast<unsigned char>(r * 255);
    desaturated[i * 3 + 1] = static_cast<unsigned char>(g * 255);
    desaturated[i * 3 + 2] = static_cast<unsigned char>(b * 255);
  }

}
