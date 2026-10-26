#include "image.hpp"

bool Image::setPixelAt(int x, int y, uint8_t color) {

    if ( x < 0 && x > this->size_x) return false;
    if ( y < 0 && y > this->size_y) return false;

    this->pixels[x * y] = color;

    return true;

}

bool Image::clear() {

    for (int i = 0; i < this->size_x * this->size_y; ++i)
        this->pixels[x * y] = 0;

    return true;

}
