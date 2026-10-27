#include <cstdint>
#include <cmath>
#include <string>
#include "logger.h"

#include "Image.hpp"

Image::Image(int size_x, int size_y) {

    this->size_x = size_x;
    this->size_y = size_y;
    this->pixels = std::vector<uint8_t>(size_x * size_y);

    this->view_unit_x = 1./this->size_x;
    this->view_unit_y = 1./this->size_y;

    this->drawing_color = 255;

    this->clear();

}

bool Image::setPixelAt(int x, int y) {

    if ( x < 0 || x >= this->size_x) return false;
    if ( y < 0 || y >= this->size_y) return false;

    this->pixels[x + y * size_x] = this->drawing_color;

    return true;

}

uint8_t Image::getPixelAt(int x, int y) {

    if ( x < 0 || x >= this->size_x) return 0;
    if ( y < 0 || y >= this->size_y) return 0;

    return this->pixels[x + y * size_x];

}

float Image::weigthUnit() {

    return this->view_unit_x;

}

float Image::heigthUnit() {

    return this->view_unit_y;

}

bool Image::setDrawingColor(uint8_t color) {

    this->drawing_color = color;
    return true;

}

bool Image::clear() {

    for (int i = 0; i < this->size_x * this->size_y; ++i)
        this->pixels.at(i) = 0;

    return true;

}

bool Image::drawGlyph(std::string glyph, float vw, float vh) {
    return true;
}


bool Image::drawText(std::string text, float vw, float vh) {
    return true;
}

bool Image::drawRect(float vw, float vh, float weight, float height) {

    int pixel_x = (int)(vw / this->view_unit_x);
    int pixel_y = (int)(vh / this->view_unit_y);
    int pixel_size_x = (int)(weight / this->view_unit_x);
    int pixel_size_y = (int)(height / this->view_unit_y);

    for (int l = 0; l < pixel_size_y; l++) {

        for(int k = 0; k < pixel_size_x; k++) {

            setPixelAt(pixel_x + l, pixel_y + k);

        }

    }

    return true;
}

bool Image::drawCircle(float vw, float vh, float radius) {

    int pixel_x = (int)(vw / this->view_unit_x);
    int pixel_y = (int)(vh / this->view_unit_y);
    float pixel_size_radius = (radius / this->view_unit_x);
    float pixel_diameter = pixel_size_radius * 2;

    for (float l = 0; l < pixel_diameter; l++) {

        for(float k = 0; k < pixel_diameter; k++) {

            // If pixel within the circle...
            if ( sqrt( pow(pixel_size_radius - l, 2) + pow(pixel_size_radius - k, 2) ) < pixel_size_radius ) {
                setPixelAt(pixel_x + k, pixel_y + l);
            }

        }

    }

    return true;
}

bool Image::drawTriangle(float vw1, float vh1, float vw2, float vh2, float vw3, float vh3) {

    return true;
}
