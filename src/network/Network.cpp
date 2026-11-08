
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

    CROW_ROUTE(this->_app, "/")
    ([&] {
        char name[256];
        gethostname(name, 256);
        crow::mustache::context x;
        x["servername"] = name;
        x["port"] = this->_port;

        auto page = crow::mustache::load("index.html");
        return page.render(x);
    });

    CROW_WEBSOCKET_ROUTE(this->_app, "/ws")
    .onopen([&](crow::websocket::connection& conn) {
        CROW_LOG_INFO << "new websocket connection from " << conn.get_remote_ip();

    })
    .onclose([&](crow::websocket::connection& conn, const std::string& reason, uint16_t) {
        CROW_LOG_INFO << "websocket connection closed: " << reason;

    })
    .onmessage([&](crow::websocket::connection& /*conn*/, const std::string& data, bool is_binary) {

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
