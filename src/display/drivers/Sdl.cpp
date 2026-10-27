
#include "Sdl.hpp"

Sdl::Sdl(int x, int y) {

    this->size_x = x;
    this->size_y = y;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(x, y, 0, &window, &renderer);

}

Sdl::~Sdl() {

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}

bool Sdl::display(Image* img) {

    if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
        return false;

    int size_x = (int)(1. / (img->weigthUnit()));
    int size_y = (int)(1. / (img->heigthUnit()));

    for (int l = 0; l <= size_y; l++) {

        for (int k = 0; k <= size_x; k++) {

            uint8_t p = img->getPixelAt(k, l);
            SDL_SetRenderDrawColor(renderer, p >> 6, (p << 2) >> 6, (p << 4) >> 6, 255);
            SDL_RenderDrawPoint(renderer, k, l);

        }

        printf("\n");

    }

    SDL_RenderPresent(renderer);


    return true;
}
