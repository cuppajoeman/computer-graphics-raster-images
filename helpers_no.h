#ifndef HELPERS_H
#define HELPERS_H

#include <utility> // for std::pair
#include <iostream>

std::pair<int, int> divmod(int numerator, int denominator);
int get_bayer_mosaic_channel(int row, int col);

#endif
