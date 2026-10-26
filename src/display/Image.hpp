#pragma once
#include <cstdint>
#include <vector>

/**
 * @class Image
 * @desc Represent an image in memory
 */
class Image {

    private:

        int size_x;
        int size_y;
        std::vector<uint8_t> pixels;

    public:

        Image(int size_x, int size_y);

        /**
         * @fn setPixelAt
         * @desc Set the color of a pixel at x, y
         */
        bool setPixelAt(int x, int y, uint8_t color);

        /**
         * @fn clear
         * @desc Clear the Image to color 0
         */
        bool clear();

};
