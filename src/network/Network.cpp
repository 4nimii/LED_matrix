
#include "Network.hpp"
#include "logger.h"


class reLogger : public crow::ILogHandler {

public:

    reLogger() {}
    void log(const std::string& message, crow::LogLevel level) {

        switch (level)
        {
            case crow::LogLevel::Debug:
                logger(0, message.c_str());
                break;
            case crow::LogLevel::Info:
                logger(1, message.c_str());
                break;
            case crow::LogLevel::Warning:
                logger(2, message.c_str());
                break;
            case crow::LogLevel::Error:
                logger(3, message.c_str());
                break;
            case crow::LogLevel::Critical:
                logger(4, message.c_str());
                break;
        }

    }

};


Network::Network( Config* conf ) {

    std::string port = conf->get( "port" );
    if ( port == "" ) {
        logger( 2, "Selecting default port 8080 as no port has been specified in configuration." );
        this->_port = 8080;
    } else
        this->_port = std::stoi( port );

}


bool Network::init() {

    CROW_ROUTE(this->_app, "/")([this](){
        auto page = crow::mustache::load_text("index.html");
        return page;
    });

    return true;
}


bool Network::run() {

    reLogger log;
    crow::logger::setHandler(&log);
    this->_app.port(this->_port).multithreaded().run();
    return true;

}
