#include "simulate_bayer_mosaic.h"
#include "helpers.h"


void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  for (int i = 0; i < width * height; i ++) {
    auto qr = divmod(i, width);
    int row = qr.first;
    int col = qr.second;

    // i only iterates through width * height, so mul by 3 makes sense
    // mul by 3 makes it get to the right rgb block
    int rgb_index = (row * width + col) * 3; 
    // based on where we are in the b.m. find which color channel we need
    int channel = get_bayer_mosaic_channel(row, col);

    bayer[i] = rgb[rgb_index + channel];
  }
}
