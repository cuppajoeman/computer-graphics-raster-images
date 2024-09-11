#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  assert(
    (num_channels == 3 || num_channels == 1) &&
    ".ppm only supports RGB or grayscale images");

  std::ofstream ppm_file(filename);

  if (!ppm_file) {
    std::cerr << "Error: Could not open file " << filename << std::endl;
    return false;
  }

  // P2 for grayscale (num_channels == 1), P3 for RGB (num_channels == 3)
  if (num_channels == 1) {
    ppm_file << "P2\n";  // Grayscale ASCII format
  } else if (num_channels == 3) {
    ppm_file << "P3\n";  // RGB ASCII format
  }

  // Write image dimensions and maximum color value
  ppm_file << width << " " << height << "\n255\n";

  // Loop through the data and write each pixel as an ASCII string
  for (int i = 0; i < height * width * num_channels; i += num_channels) {
    for (int j = 0; j < num_channels; ++j) {
      // Convert each `unsigned char` to an integer and output it as a string
      ppm_file << static_cast<int>(data[i + j]) << " ";
    }
    ppm_file << "\n";
  }

  ppm_file.close();
  return true;
}
