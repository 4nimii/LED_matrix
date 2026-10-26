#include "MainMenu.hpp"

MainMenu::MainMenu(std::vector<Game*> games) {

    current_game = -1;
    this->games = games;

}
bool MainMenu::addPlayer(Player* p) {

    // The player is already here ?
    if ( getPlayerIndex(p) != -1 ) return false;

    this->players.push(p);
    this->voted_for.push(-1);

    // Also add the player to the running game...
    if ( current_game >= 0 ) {

        this->games.at(current_game)->addPlayer(p);

    }

    return true;

}

int MainMenu::getPlayerIndex(Player* p) {

    for (int i = 0; i < this->players.length; ++i) {

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

    if (player_index == -1) return false

    // We need at least 2 parameters
    if ( v.length >= 2 ) {

        // Vote action
        if ( v[0] == 0 ) {

            // If Action Value is in correct range...
            if ( v[1] < this->games.length ) {

                // Mark the vote for game n in the voted for array
                this->voted_for.at(player_index) = v[1];
                return true;

            }

        }

    }

}

int MainMenu::mostVotedGame() {

    std::vector<int> game_score( this->games.length + 1 );

    for ( int v: this->voted_for ) {

        // Not voted or neutral state
        if ( v < 0 ) {

            game_score.at(0) += 1;

        } else {

            game_score.at(v + 1) += 1;

        }

    }

    int max = 0;
    for ( int i = 0; i < game_score.length; ++i ) {

        if ( game_score.at(max) < game_score.at(i) ) {

            max = i;

        }

    }

    return max;

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
            next_game.addPlayer(p);

    }

    // update the running game
    if ( current_game < 0 )
        this->games.at(current_game)->update();

}

bool MainMenu::isRunning() {

    return true;

}

bool MainMenu::render(Image[]* i) {

    if ( current_game < 0 )
        this->games.at(current_game)->render(i);
    else
        void; // Render main menu, later

}

bool MainMenu::reset() {

    this->players.clear();
    this->next_game_vote.clear();
    this->voted_for.clear();
    current_game = -1;

}
