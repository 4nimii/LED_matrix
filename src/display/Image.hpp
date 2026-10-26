#pragma once
#include <cstdint>
#include <vector>
#include <string>

/**
 * @class Image
 * @desc Represent an image in memory. It allow to easily draw shapes and text using screen space coordinates.
 */
class Image {

    private:

        int size_x;
        int size_y;
        std::vector<uint8_t> pixels;
        uint8_t drawing_color;
        float view_unit_x;
        float view_unit_y;

    public:

        Image(int size_x, int size_y);

        /**
         * @fn getPixelAt
         * @desc Return pixel at x, y
         */
        uint8_t getPixelAt(int x, int y);

        /**
         * @fn setPixelAt
         * @desc Color pixel at x, y
         */
        bool setPixelAt(int x, int y);

        /**
         * @fn setDrawingColor
         * @desc Change the drawing color
         */
        bool setDrawingColor(uint8_t color);

        /**
         * @fn clear
         * @desc Clear the Image to color 0
         */
        bool clear();

        /**
         * @fn weigthUnit
         * @desc Return the value if 1 pixel in screen space for the x axis
         */
        float weigthUnit();


        /**
         * @fn heigthUnit
         * @desc Return the value if 1 pixel in screen space for the y axis
         */
        float heigthUnit();

        /**
         * @fn displayGlyph
         * @desc Display a glyph at defined coordinates
         */
        bool displayGlyph(std::string glyph, float vw, float vh);

        /**
         * @fn displayText
         * @desc Display text at defined coordinates
         */
        bool displayText(std::string text, float vw, float vh);

        /**
         * @fn displayRect
         * @desc Display a rectangle at defined coordinates
         */
        bool displayRect(float vw, float vh, float weight, float height);

        /**
         * @fn displayCircle
         * @desc Display a circle at defined coordinates
         */
        bool displayCircle(float vw, float vh, float radius);

        /**
         * @fn displayTriangle
         * @desc Display a triangle at defined coordinates
         */
        bool displayTriangle(float vw1, float vh1, float vw2, float vh2, float vw3, float vh3);

};
