#include <cmath>

#include "MainMenu.hpp"

MainMenu::MainMenu(std::vector<Game*> games) {

    current_game = -1;
    this->games = games;

}
bool MainMenu::addPlayer(Player* p) {

    // The player is already here ?
    if ( getPlayerIndex(p) != -1 ) return false;

    this->players.push_back(p);
    this->voted_for.push_back(-1);

    // Also add the player to the running game...
    if ( current_game >= 0 ) {

        this->games.at(current_game)->addPlayer(p);

    }

    return true;

}

int MainMenu::getPlayerIndex(Player* p) {

    for (int i = 0; i < this->players.size(); ++i) {

        // Found the player...
        if (this->players.at(i)->getID() == p->getID()) {

            return i;

        }

    }

    // Player not in game
    return -1;

}

bool MainMenu::removePlayer(Player* p) {

    int player_index = getPlayerIndex(p);

    // Player not in game
    if (player_index == -1) return false;

    this->players.erase(this->players.begin() + player_index);
    this->voted_for.erase(this->voted_for.begin() + player_index);

    // Also remove the player from the running game...
    if ( current_game >= 0 ) {

        this->games.at(current_game)->removePlayer(p);

    }

    return false;

}

bool MainMenu::updatePlayer(Player* p, std::vector<int> v) {

    int player_index = getPlayerIndex(p);

    if (player_index == -1) return false;

    // We need at least 2 parameters
    if ( v.size() >= 2 ) {

        // Vote action
        if ( v[0] == 0 ) {

            // If Action Value is in correct range...
            if ( v[1] < this->games.size() ) {

                // Mark the vote for game n in the voted for array
                this->voted_for.at(player_index) = v[1];
                return true;

            }

        }

    }

    return false;

}

int MainMenu::mostVotedGame() {

    std::vector<int> game_score( this->games.size() + 1 );

    for ( int v: this->voted_for ) {

        // Not voted or neutral state
        if ( v < 0 ) {

            game_score.at(0) += 1;

        } else {

            game_score.at(v + 1) += 1;

        }

    }

    int max = 0;
    for ( int i = 0; i < game_score.size(); ++i ) {

        if ( game_score.at(max) < game_score.at(i) ) {

            max = i;

        }

    }

    return max - 1;

}

bool MainMenu::update() {

    int next_game = mostVotedGame();

    // We change of game...
    if ( next_game != current_game ) {

        // if the current game is a game and not the main menu (main menu = -1, neutral vote);
        if (current_game >= 0)
            this->games.at(current_game)->reset();

        current_game = next_game;

        for (Player* p: this->players)
            this->games.at(current_game)->addPlayer(p);

    }

    // update the running game
    if ( current_game >= 0 )
        this->games.at(current_game)->update();

    return true;

}

bool MainMenu::isRunning() {

    return true;

}

bool MainMenu::render(Image* i) {

    i->clear();
    iterations += 1;

    if ( current_game >= 0 )
        this->games.at(current_game)->render(i);
    else {
        i->setDrawingColor(142);
        i->drawRect(0.1, 0.05, std::abs(std::cos(iterations * i->weigthUnit() * 2)), std::abs(std::cos(iterations * i->heigthUnit())));
        i->setDrawingColor(255);
        i->drawCircle(0.2, std::abs(std::cos(iterations * i->weigthUnit() * 10)), std::abs(std::cos(iterations * i->weigthUnit() * 2))/2);
        i->setDrawingColor(63);
        i->drawTriangle(0.2, std::abs(std::cos(iterations * i->weigthUnit() * 10)), std::abs(std::cos(iterations * i->weigthUnit() * 2))/2, 0.7, 0.3, 0.2);
        i->setDrawingColor(255);
        i->drawText("Hello world", 0., std::abs(std::cos(iterations * i->weigthUnit() * 2)), 1., .1);
    }

    return true;

}

bool MainMenu::reset() {

    this->players.clear();
    this->next_game_vote.clear();
    this->voted_for.clear();
    current_game = -1;

    return true;

}
