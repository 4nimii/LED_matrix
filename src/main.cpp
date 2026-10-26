#include "logger.h"

#include "games/Game.hpp"
#include "games/MainMenu.hpp"
#include "display/Image.hpp"
#include "display/Display.hpp"
#include "display/drivers/Stdout.hpp"

int main(int argc, char** argv) {

    logger(0, "-- LED Matrix Start --");

    std::vector<Game*> games;

    logger(0, "- Loaded games");

    MainMenu* menu = new MainMenu(games);

    logger(0, "- Loaded Main Menu");

    // select correct size with argv, argc
    Image* screen = new Image(32, 32);

    logger(0, "- Loaded Image (screen)");

    // select correct driver with argv, argc
    Display* display = new Stdout();

    logger(0, "- Loaded Display");

    logger(0, "-- LED Matrix loaded --");

    while (true) {

        menu->update();
        menu->render(screen);
        display->display(screen);

    }

}
