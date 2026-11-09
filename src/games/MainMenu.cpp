#include "MainMenu.hpp"
#include "logger.h"
#include <cstdint>
#include <string>

#include "../network/Player.hpp"


MainMenu::MainMenu( std::vector<Game*> games ) {

    this->_current_game = -1;
    this->_games = games;

    this->_cube = {
        new Vec3(0.5, 0.5, 0.5), new Vec3(0.5, 0.5, -0.5), new Vec3(0.5, -0.5, 0.5), new Vec3(0.5, -0.5, -0.5),
        new Vec3(-0.5, 0.5, 0.5), new Vec3(-0.5, 0.5, -0.5), new Vec3(-0.5, -0.5, 0.5), new Vec3(-0.5, -0.5, -0.5)
    };

    this->_camera = new Camera();

}


bool MainMenu::addPlayer( Player* p ) {

    // The player is already here ?
    if ( _getPlayerIndex( p ) != -1 ) return false;

    this->_players.push_back( p );
    this->_voted_for.push_back( -1 );

    // Also add the player to the running game...
    if ( this->_current_game >= 0 ) {

        this->_games.at( this->_current_game )->addPlayer( p );

    }

    logger( 1, ( "Added player with ID: " + p->getID() ).c_str() );

    return true;

}


int MainMenu::_getPlayerIndex( Player* p ) {

    for ( int i = 0; i < this->_players.size(); ++i ) {

        // Found the player...
        if ( this->_players.at( i )->getID() == p->getID() ) {

            return i;

        }

    }

    // Player not in game
    return -1;

}


bool MainMenu::removePlayer( Player* p ) {

    int player_index = _getPlayerIndex( p );

    // Player not in game
    if ( player_index == -1 ) return false;

    this->_players.erase( this->_players.begin() + player_index );
    this->_voted_for.erase( this->_voted_for.begin() + player_index );

    // Also remove the player from the running game...
    if ( this->_current_game >= 0 ) {

        this->_games.at( this->_current_game )->removePlayer( p );

    }

    logger( 1, ( "Removed player with ID: " + p->getID() ).c_str() );

    return true;

}


bool MainMenu::updatePlayer( Player* p, std::vector<Value> v) {

    std::string request = "[ ";
    for ( Value l: v ) {
        if ( l.string == nullptr )
        request += std::to_string(*l.number) + ", ";
    }
    request += " ]";
    logger( 1, ( "Received request: " + request + " from player with ID: " + p->getID() ).c_str() );

    int player_index = _getPlayerIndex( p );

    if ( player_index == -1 ) return false;

    // We need at least 2 parameters
    if ( v.size() >= 2 && v[0].number != nullptr ) {

        switch (*v[0].number) {

            // Vote
            case 0:
                if ( v[1].number != nullptr && *v[1].number < this->_games.size() ) {

                    // Mark the vote for game n in the voted for array
                    this->_voted_for[player_index] = *v[1].number;
                    return true;

                }

            // Pass to current game
            case 1:
                if ( this->_current_game >= 0 ) {
                    v.erase(v.begin());
                    return this->_games[this->_current_game]->updatePlayer( p, v );
                }


        }

    }

    return false;

}


int MainMenu::_mostVotedGame() {

    std::vector<int> game_score( this->_games.size() + 1 );

    for ( int v: this->_voted_for ) {

        // Not voted or neutral state
        if ( v < 0 ) {

            game_score[0] += 1;

        } else {

            game_score[v + 1] += 1;

        }

    }

    int max = 0;
    for ( int i = 0; i < game_score.size(); ++i ) {

        if ( game_score[max] < game_score[i] ) {

            max = i;

        }

    }

    return max - 1;

}


bool MainMenu::update() {

    int next_game = _mostVotedGame();

    // We change of game...
    if ( next_game != this->_current_game ) {

        // if the current game is a game and not the main menu (main menu = -1, neutral vote);
        if ( this->_current_game >= 0 )
            this->_games[this->_current_game]->reset();

        this->_current_game = next_game;

        for ( Player* p: this->_players )
            this->_games[this->_current_game]->addPlayer( p );

    }

    // update the running game
    if ( this->_current_game >= 0 )
        this->_games[this->_current_game]->update();

    return true;

}


bool MainMenu::isRunning() {

    return true;

}


bool MainMenu::render( Image* img ) {

    if ( this->_iterations == 0 ) {
        initCamera( img, this->_camera, 30 );
    }

    img->clear();
    this->_iterations += 1;

    if ( this->_current_game >= 0 )
        this->_games[this->_current_game]->render( img );

    else {

        float height = 1./this->_players.size();
        for ( int i = 0; i < this->_players.size(); i++ ) {

            img->drawText( this->_players[i]->getName(), 0., height * i, 1., height);

        }

    }

    return true;

}



bool MainMenu::reset() {

    this->_players.clear();
    this->_next_game_vote.clear();
    this->_voted_for.clear();
    this->_current_game = -1;

    return true;

}
