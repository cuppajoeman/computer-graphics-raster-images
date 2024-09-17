#include "hsv_to_rgb.h"
#include <cmath>

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
    const double epsilon = 1e-6; // small tolerance for comparisons

    // if saturation is close to 0, the color is a shade of gray (no hue)
    if (s < epsilon) {
        r = g = b = v; // grayscale color
        return;
    }

    // normalize hue to the range [0, 360)
    double normalized_h = std::fmod(h, 360.0);
    if (normalized_h < 0) {
        normalized_h += 360.0;
    }

    // divide hue by 60 to find the hue sector (0 to 5)
    double hue_sector = normalized_h / 60.0;
    int sector_index = static_cast<int>(std::floor(hue_sector)); // which sector (0 to 5)

    // determine the fractional part of the hue sector
    double fractional_sector = hue_sector - sector_index;

    // compute intermediate values for the rgb components
    double p = v * (1.0 - s);
    double q = v * (1.0 - s * fractional_sector);
    double t = v * (1.0 - s * (1.0 - fractional_sector));

    // assign rgb values based on the hue sector
    switch (sector_index) {
        case 0: // hue is between 0 and 60 (red to yellow)
            r = v;
            g = t;
            b = p;
            break;
        case 1: // hue is between 60 and 120 (yellow to green)
            r = q;
            g = v;
            b = p;
            break;
        case 2: // hue is between 120 and 180 (green to cyan)
            r = p;
            g = v;
            b = t;
            break;
        case 3: // hue is between 180 and 240 (cyan to blue)
            r = p;
            g = q;
            b = v;
            break;
        case 4: // hue is between 240 and 300 (blue to magenta)
            r = t;
            g = p;
            b = v;
            break;
        case 5: // hue is between 300 and 360 (magenta to red)
            r = v;
            g = p;
            b = q;
            break;
    }
}
