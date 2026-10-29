#include "logger.h"
#include <chrono>
#include <thread>

#include "games/Game.hpp"
#include "games/MainMenu.hpp"
#include "display/Image.hpp"
#include "display/Display.hpp"
#include "display/drivers/Sdl.hpp"

int main(int argc, char** argv) {

    using namespace std::this_thread;
    using namespace std::chrono_literals;
    using std::chrono::system_clock;

    logger(0, "-- LED Matrix Start --");

    std::vector<Game*> games;

    logger(0, "- Loaded games");

    MainMenu* menu = new MainMenu(games);

    logger(0, "- Loaded Main Menu");

    // select correct size with argv, argc
    Image* screen = new Image(128, 128);
    screen->loadFont("build/EBGaramond-Regular.ttf");

    logger(0, "- Loaded Image (screen)");

    // select correct driver with argv, argc
    Display* display = new Sdl(512, 512);

    logger(0, "- Loaded Display");

    logger(0, "-- LED Matrix loaded --");

    while (true) {

        menu->update();
        menu->render(screen);

        // For instance we closed the Window
        if (!display->display(screen)) {
            delete display;
            return 0;
        }

        //Just to avoid to use all of the CPU because we try to render at 65465 frames/seconds
        sleep_for(1ms);

    }

}
