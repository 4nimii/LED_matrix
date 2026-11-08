
#include "Player.hpp"
#include <string>
#include <vector>


Player::Player( crow::websocket::connection* connection ) {

    this->_connection = connection;

}

std::string Player::getID() {

    return this->_connection->get_remote_ip() + ":" + std::to_string(this->_connection->get_remote_port());

}


bool Player::setName( std::string n ) {

    this->_name = n;
    return true;

}


std::string Player::getName() {

    return this->_name;

}


bool Player::updateGame( std::string r ) {

    std::vector<int> request;
    size_t pos = 0;
    std::string token;

    while ( ( pos = r.find( ',' ) ) != std::string::npos ) {
        token = r.substr( 0, pos );
        request.push_back( std::stoi( token ) );
        r.erase( 0, pos + 1 );
    }
    request.push_back( std::stoi( token ) );

    return this->_game->updatePlayer( this, request );

}


bool Player::setGame( Game* g ) {

    this->_game = g;
    return this->_game->addPlayer( this );

}


bool Player::exitGame() {

    return this->_game->removePlayer( this );

}
