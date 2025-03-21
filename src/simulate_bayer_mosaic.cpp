#include "simulate_bayer_mosaic.h"
/*#include "helpers.h"*/

namespace SBM {
std::pair<int, int> divmod(int numerator, int denominator) {
    int quotient = numerator / denominator;
    int remainder = numerator % denominator;
    return std::make_pair(quotient, remainder);
}
int get_bayer_mosaic_channel(int row, int col) {
    int r = 0, g = 1, b = 2;
    if (row % 2 == 0) {
        if (col % 2 == 0) {
            return g;
        } else {
            return b;
        }
    } else {
        if (col % 2 == 0) {
            return r;
        } else {
            return g;
        }
    }
}
}


void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  for (int i = 0; i < width * height; i ++) {
    auto qr = SBM::divmod(i, width);
    int row = qr.first;
    int col = qr.second;

    // i only iterates through width * height, so mul by 3 makes sense
    // mul by 3 makes it get to the right rgb block
    int rgb_index = (row * width + col) * 3; 
    // based on where we are in the b.m. find which color channel we need
    int channel = SBM::get_bayer_mosaic_channel(row, col);

    bayer[i] = rgb[rgb_index + channel];
  }
}
