#include "helpers.h"

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
