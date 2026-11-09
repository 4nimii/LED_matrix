
#include "Network.hpp"
#include "Player.hpp"


Network::Network( Config* conf, MainMenu* main ) {

    std::string port = conf->get( "port" );
    if ( port == "" ) {
        logger( 2, "Selecting default port 8080 as no port has been specified in configuration." );
        this->_port = 8080;
    } else
        this->_port = std::stoi( port );

    this->_game = main;

}


int Network::getPlayerIndexByConnection( crow::websocket::connection* c ) {

    for ( int i = 0; i < this->_players.size(); i++ ) {

        if ( this->_players[i]->getConnection() == c )
            return i;

    }

    return -1;

}


std::vector<Value> Network::parseRequest( const std::string& data ) {

    std::vector<Value> request;
    size_t start = 0;

    while ( true ) {

        size_t pos = data.find( ',', start );
        std::string token = data.substr( start, pos == std::string::npos ? std::string::npos : pos - start );

        Value v;
        if ( token.length() == 1 && token[0] >= '0' && token[0] <= '9' )
            v.number = static_cast<uint8_t>( token[0] - '0' );
        else
            v.string = token;
        request.push_back( v );

        if ( pos == std::string::npos ) break;
        start = pos + 1;

    }

    return request;

}


bool Network::init() {

    CROW_ROUTE( this->_app, "/" )
        ([&] {

            char name[256];
            gethostname( name, 256 );
            crow::mustache::context x;
            x["servername"] = name;
            x["port"] = this->_port;

            auto page = crow::mustache::load( "index.html" );
            return page.render( x );

        });

    CROW_WEBSOCKET_ROUTE( this->_app, "/ws" )
        .onopen([&]( crow::websocket::connection& conn ) {

            CROW_LOG_INFO << "new websocket connection from " << conn.get_remote_ip();
            std::lock_guard<std::mutex> lock( this->_players_mutex );
            Player* new_p = new Player( &conn );
            new_p->setName( "Player " + std::to_string(this->_players.size()) );
            new_p->setGame( this->_game );
            this->_players.push_back( new_p );

        })
        .onclose([&]( crow::websocket::connection& conn, const std::string& reason, uint16_t ) {

            CROW_LOG_INFO << "websocket connection closed: " << reason;
            std::lock_guard<std::mutex> lock( this->_players_mutex );
            int p = getPlayerIndexByConnection( &conn );
            if ( p == -1 ) return;

            Player* player = this->_players[p];
            this->_players.erase( this->_players.begin() + p );
            // Removed from the menu (under its lock) before being freed,
            // so the render loop can no longer reference it.
            player->exitGame();
            delete player;

        })
        .onmessage([&]( crow::websocket::connection& conn, const std::string& data, bool is_binary ) {

            std::vector<Value> request = parseRequest( data );

            std::lock_guard<std::mutex> lock( this->_players_mutex );
            int p = getPlayerIndexByConnection( &conn );
            if ( p == -1 ) return;
            this->_players[p]->updateGame( request );

        });

    return true;
}


bool Network::run() {

    static reLogger crow_logger;
    crow::logger::setHandler( &crow_logger );
    this->_crow_thread = this->_app.port( this->_port ).run_async();
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

    // Crow is stopped: no more callbacks can touch _players.
    for ( Player* p: this->_players ) {
        p->exitGame();
        delete p;
    }
    this->_players.clear();

}
