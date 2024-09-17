#include "reflect.h"
#include "helpers.h"


void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);

  for (int i = 0; i < input.size(); i += num_channels) {
    auto qr = divmod(i / num_channels, width);
    int row = qr.first; int col = qr.second;

    int reflected_col = width - 1 - col;
    int reflected_index = (row * width + reflected_col) * num_channels;

    // copy over the color channels
    for (int channel = 0; channel < num_channels; ++channel) {
      reflected[reflected_index + channel] = input[i + channel];
    }
  }
}
