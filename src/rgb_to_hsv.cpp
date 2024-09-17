#include "rgb_to_hsv.h"
#include <algorithm>
#include <cmath>

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
    double maximum_color_intensity = std::max({r, g, b});
    double minimum_color_intensity = std::min({r, g, b});
    double color_intensity_range = maximum_color_intensity - minimum_color_intensity;
    
    v = maximum_color_intensity; // brightness
    
    // saturation calculation
    const double epsilon = 1e-6; // small tolerance for comparison
    if (maximum_color_intensity < epsilon) {
        s = 0; // black or very close to black
    } else {
        s = color_intensity_range / maximum_color_intensity;
    }
    
    // hue calculation
    if (color_intensity_range < epsilon) {
        h = 0; // grayscale, so no hue
    } else {
        if (maximum_color_intensity == r) {
            h = (g - b) / color_intensity_range;
        } else if (maximum_color_intensity == g) {
            h = 2.0 + (b - r) / color_intensity_range;
        } else {
            h = 4.0 + (r - g) / color_intensity_range;
        }

        // convert hue to degrees and clamp to [0, 360)
        h *= 60.0;
        h = fmod(h, 360.0);
        if (h < 0) {
            h += 360.0;
        }
    }
}
