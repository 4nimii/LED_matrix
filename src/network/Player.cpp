#include <cstdint>
#include <string>
#include <vector>

#include "Player.hpp"
#include "../utils/request.hpp"
#include "logger.h"


Player::Player( crow::websocket::connection* connection ) {

    this->_connection = connection;
    this->_name = "";

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


bool Player::updateGame( std::vector<Value> request ) {

    if ( request[0].number != nullptr && *request[0].number == 0 ) {


        if ( request[1].string != nullptr ) {

            return this->setName( *(request[1].string) );

        } else {

            return false;

        }

    }

    request.erase(request.begin());
    return this->_game->updatePlayer( this, request );

}


bool Player::setGame( Game* g ) {

    this->_game = g;
    return this->_game->addPlayer( this );

}


bool Player::exitGame() {

    return this->_game->removePlayer( this );

}
