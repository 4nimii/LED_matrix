

#include "games/Game.hpp"
#include "games/MainMenu.hpp"
#include "games/Pong.hpp"
#include "display/Image.hpp"
#include "display/Display.hpp"

int main(int argc, char** argv) {

    std::vector<Game*> games;
    games.push_back( (Game*)new Pong() );

    MainMenu* menu = new MainMenu(games);
    Image* screen = new Image(128, 128);
    // Display* diplay, select correct driver with argv, argc

    while (true) {

        menu->update();
        menu->render(screen);
        // display render

    }

}
