// Use a Image rendered by a Game to display it on a screen
// Dispay is the mother class for all Drivers
// Even if the Image is bigger than the final screen resolution, the Driver should be able to scale it.
#pragma once
#include "Image.hpp"

class Display {

    public:

        virtual bool display(Image* ) = 0;
        virtual ~Display() = default;

};
