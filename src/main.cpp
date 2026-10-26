

#include "games/Game.hpp"
#include "games/MainMenu.hpp"
#include "games/Pong.hpp"
#include "display/Image.hpp"
#include "display/Display.hpp"

int main(int argc, char** argv) {

    std::vector<Game*> games;
    games.push( (Game*)new Pong() );

    MainMenu* menu(games);
    Image* screen = new Image();
    // Display* diplay, select correct driver with argv, argc

    while (true) {

        menu.update();
        menu.render(screen);
        // display render

    }

}
