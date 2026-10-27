#pragma once
#include "../Display.hpp"

class Stdout: public Display {

    public:

        ~Stdout() = default;
        bool display(Image* ) override;

};
