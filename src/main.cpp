#include "logger.h"
#include <thread>

#include "games/Game.hpp"
#include "games/MainMenu.hpp"
#include "display/Image.hpp"
#include "display/Display.hpp"
#include "display/drivers/Sdl.hpp"
#include "utils/Config.hpp"
#include "network/Network.hpp"


using namespace std::this_thread;
using namespace std::chrono_literals;


void runServer( Network* s ) {

    s->run();

    return;

}


int main( int argc, char** argv ) {


    if ( argc != 2 ) {

        logger( 3, "Missing parameters: [exe] <config file>" );
        return 1;

    }

    Config* conf = new Config();
    if ( conf->parse( argv[1] ) ) return 1;

    std::string font_path = conf->get("font_path");

    logger( 0, "-- LED Matrix Start --" );

    std::vector<Game*> games;

    logger( 0, "- Loaded games" );

    MainMenu* menu = new MainMenu( games );

    logger( 0, "- Loaded Main Menu" );

    Image* screen = new Image( std::stoi( conf->get("matrix_x_size") ), std::stoi( conf->get("matrix_y_size") ) );
    screen->loadFont( font_path );

    logger( 0, "- Loaded Image (screen)" );

    Display* display;
    if ( conf->get("driver") == "sdl")
        display = new Sdl( conf );

    logger( 0, "- Loaded Display" );

    Network* server = new Network( conf );
    server->init();
    std::thread t( runServer, server );

    logger( 0, "- Server loaded & Running" );

    logger( 0, "-- LED Matrix loaded --" );

    while ( true ) {

        menu->update();
        menu->render( screen );

        // For instance we closed the Window
        if ( !display->display( screen ) ) {

            delete display;
            return 0;

        }

        //Just to avoid to use all of the CPU because we try to render at 65465 frames/seconds
        sleep_for( 1ms );

    }

    return 0;

}
