#pragma once
#include <cstdint>
#include <vector>
#include <string>

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

        // -- x, y / size in display functions could be not in pixels but screen coordinates, else screen size should be accessible

        /**
         * @fn displayGlyph
         * @desc Display a glyph at defined coordinates
         */
        bool displayGlyph(char glyph, float x, float y);

        /**
         * @fn displayText
         * @desc Display text at defined coordinates
         */
        bool displayText(std::string text, float x, float y);

        /**
         * @fn displayRect
         * @desc Display a rectangle at defined coordinates
         */
        bool displayRect(float x, float y, float size_x, float size_y);

        /**
         * @fn displayCircle
         * @desc Display a circle at defined coordinates
         */
        bool displayCircle(float x, float y, float radius);

};
