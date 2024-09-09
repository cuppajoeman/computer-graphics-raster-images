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
    (num_channels == 3 || num_channels ==1 ) &&
    ".ppm only supports RGB or grayscale images");

  std::ofstream ppm_file(filename, std::ios::binary);

  if (!ppm_file) {
    return true;
  }

  ppm_file << "P6\n";
  ppm_file << width << " " << height << "\n";
  ppm_file << "255\n";

  const char* type_converted_data = reinterpret_cast<const char*>(data.data());
  ppm_file.write(type_converted_data, data.size());


  return false;
}
