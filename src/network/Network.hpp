
#include "crow.h"
#include "crow/middlewares/cors.h"
#include "../utils/Config.hpp"


class Network {

    private:

        crow::App<crow::CORSHandler> _app;
        int _port;
        std::string _url;

    public:

        Network( Config* conf );
        bool init();
        bool run();

};
