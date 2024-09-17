#include "rotate.h"
#include "helpers.h"

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // 
  // Original Image (Width = 4, Height = 3):
  // 
  // Row 0:  0   1   2   3
  // Row 1:  4   5   6   7
  // Row 2:  8   9  10  11
  // 
  // Rotated Image (90 degrees counterclockwise):
  // 
  // Row 0:  3   7  11
  // Row 1:  2   6  10
  // Row 2:  1   5   9
  // Row 3:  0   4   8
  // 
  // Transformation for each pixel:
  // - For each pixel at (row, col) in the original image, 
  //   its new position in the rotated image is:
  //     new_row = width - 1 - col
  //     new_col = row
  ////////////////////////////////////////////////////////////////////////////

  for (int i = 0; i < input.size(); i += num_channels) {
    auto qr = divmod(i / num_channels, width); // divide by num_channels to get pixel index
    int row = qr.first;
    int col = qr.second;

    int new_row = width - 1 - col;
    int new_col = row;

    int rotated_index = (new_row * height + new_col) * num_channels;

    for (int channel = 0; channel < num_channels; ++channel) {
      rotated[rotated_index + channel] = input[i + channel];
    }
  }
}
