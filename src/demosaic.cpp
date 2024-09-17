#include "demosaic.h"
#include "helpers.h"
#include <tuple>

std::tuple<unsigned char, unsigned char, unsigned char> average_of_neighbors(
    const std::vector<unsigned char>& bayer,
    int width,
    int height,
    int row,
    int col
) {
    int r_sum = 0, g_sum = 0, b_sum = 0;
    int r_count = 0 ,g_count = 0, b_count = 0;

    const int offsets[9][2] = {
        { -1, -1 }, // top-left diagonal
        { -1, 0 },  // top
        { -1, 1 },  // top-right diagonal
        { 0, -1 },  // left
        { 0, 0 },   // original pixel
        { 0, 1 },   // right
        { 1, -1 },  // bottom-left diagonal
        { 1, 0 },   // bottom
        { 1, 1 }    // bottom-right diagonal
    };

    for (const auto& offset : offsets) {
        int neighbor_row = row + offset[0];
        int neighbor_col = col + offset[1];
        if (neighbor_row >= 0 && neighbor_row < height && neighbor_col >= 0 && neighbor_col < width) {
            int index = neighbor_row * width + neighbor_col;
            int bayer_value = bayer[index];
            int channel = get_bayer_mosaic_channel(neighbor_row, neighbor_col);
            switch (channel) {
                case 0: // red
                    r_sum += bayer_value;
                    r_count += 1;
                    break;
                case 1: // green
                    g_sum += bayer_value;
                    g_count += 1;
                    break;
                case 2: // blue
                    b_sum += bayer_value;
                    b_count += 1;
                    break;
            }
            
        }
    }

    unsigned char avg_r = r_count > 0 ? static_cast<unsigned char>(r_sum / r_count) : 0;
    unsigned char avg_g = g_count > 0 ? static_cast<unsigned char>(g_sum / g_count) : 0;
    unsigned char avg_b = b_count > 0 ? static_cast<unsigned char>(b_sum / b_count) : 0;

    return std::make_tuple(avg_r, avg_g, avg_b);
}

void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  
  for (int i = 0; i < width * height; i++) {
    auto qr = divmod(i, width);
    int row = qr.first;
    int col = qr.second;

    int rgb_block_idx = (row * width + col) * 3;

    unsigned char avg_r, avg_g, avg_b;
    std::tie(avg_r, avg_g, avg_b) = average_of_neighbors(bayer, width, height, row, col);
    rgb[rgb_block_idx + 0] = avg_r; rgb[rgb_block_idx + 1] = avg_g; rgb[rgb_block_idx + 2] = avg_b;
  }

}
