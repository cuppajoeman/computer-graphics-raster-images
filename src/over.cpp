#include "over.h"
#include <array>

std::array<float, 4> blend_pixel(
    const std::array<float, 4>& A_pixel, // rgba values from A
    const std::array<float, 4>& B_pixel  // rgba values from B
) {
    float A_alpha = A_pixel[3]; // alpha value of A (0.0 to 1.0)
    float B_alpha = B_pixel[3]; // alpha value of B (0.0 to 1.0)

    // compute the final rgba values using the over formula
    std::array<float, 4> C_pixel;
    for (int i = 0; i < 3; ++i) {
        C_pixel[i] = A_alpha * A_pixel[i] + (1.0f - A_alpha) * B_pixel[i]; // rgb blending
    }
    // think of this equation like this, A has an alpha value which determines how
    // transparent it is, where 1 is completely opaque and 0 is transparent
    // if you are .75 percent there, then you have .25 remaining out of the remaining
    // you take B's regular percentage of that and add them up.
    C_pixel[3] = A_alpha + (1.0f - A_alpha) * B_alpha; // alpha blending

    return C_pixel;
}

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());

  // iterate over each pixel in the image
  for (int i = 0; i < width * height; ++i) {
      // extract the rgba values for the current pixel from image A and B
      std::array<float, 4> A_pixel = {
          A[i * 4 + 0] / 255.0f, // red
          A[i * 4 + 1] / 255.0f, // green
          A[i * 4 + 2] / 255.0f, // blue
          A[i * 4 + 3] / 255.0f  // alpha
      };

      std::array<float, 4> B_pixel = {
          B[i * 4 + 0] / 255.0f, // red
          B[i * 4 + 1] / 255.0f, // green
          B[i * 4 + 2] / 255.0f, // blue
          B[i * 4 + 3] / 255.0f  // alpha
      };

      // blend the two pixels using the over operator
      std::array<float, 4> C_pixel = blend_pixel(A_pixel, B_pixel);

      // store the result in C, converting back to unsigned char 
      C[i * 4 + 0] = static_cast<unsigned char>(C_pixel[0] * 255);
      C[i * 4 + 1] = static_cast<unsigned char>(C_pixel[1] * 255);
      C[i * 4 + 2] = static_cast<unsigned char>(C_pixel[2] * 255);
      C[i * 4 + 3] = static_cast<unsigned char>(C_pixel[3] * 255);
  }
}
