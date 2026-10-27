#pragma once
#include <SDL2/SDL.h>

#include "../Display.hpp"

class Sdl: public Display {

    private:

        int size_x;
        int size_y;
        SDL_Event event;
        SDL_Renderer* renderer;
        SDL_Window* window;

    public:

        Sdl(int x, int y);
        ~Sdl();
        bool display(Image* ) override;

};
