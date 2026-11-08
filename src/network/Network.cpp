
#include "Network.hpp"


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

    this->_logger = new reLogger();
    crow::logger::setHandler(this->_logger);
    this->_crow_thread = this->_app.port(this->_port).run_async();
    this->_app.signal_clear();
    return true;

}


bool Network::stop() {

    this->_app.stop();
    return true;

}


Network::~Network() {

    this->stop();
    if (this->_crow_thread.valid())
        this->_crow_thread.get();

}
