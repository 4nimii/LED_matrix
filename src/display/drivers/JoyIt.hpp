#pragma once
#include "../Display.hpp"
#include <vector>


typedef struct {
    int size_x;
    int size_y;
    int position_x;
    int position_y;
} LED_Screen;


/**
 * @class JoyIt
 * @brief Display driver for HUB75 LED matrix hardware.
 * Translation layer wrapping the legacy panel_output driver.
 * @param int Horizontal size of the LED matrix in pixels.
 * @param int Vertical size of the LED matrix in pixels.
 */
class JoyIt : public Display {

    private:

        int _width;
        int _height;
        std::vector<LED_Screen> _screens;

    public:

        JoyIt(  Config* conf  );
        ~JoyIt();
        bool display(Image* img) override;

};
