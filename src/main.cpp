

#include "games/Game.hpp"
#include "games/MainMenu.hpp"
#include "games/Pong.hpp"
#include "display/Image.hpp"
#include "display/Display.hpp"
#include "display/drivers/Stdout.hpp"

int main(int argc, char** argv) {

    std::vector<Game*> games;
    games.push_back( (Game*)new Pong() );

    MainMenu* menu = new MainMenu(games);

    // select correct size with argv, argc
    Image* screen = new Image(128, 128);

    // select correct driver with argv, argc
    Display* display = new Stdout();

    while (true) {

        menu->update();
        menu->render(screen);
        display->display(screen);

    }

}
