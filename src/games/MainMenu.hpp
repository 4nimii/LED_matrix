#include <vector>

#include "Game.hpp"

/**
 * @class MainMenu
 * @desc Program Main menu, manage and lauch all the other games.
 */
class MainMenu: public Game {

    private:

        std::vector<Player*> players;
        std::vector<int> next_game_vote;
        std::vector<Game*> games;
        std::vector<int> voted_for;
        int current_game;

        int getPlayerIndex(Player* );
        int mostVotedGame();

    public:

        MainMenu(std::vector<Game*> games);
        override bool addPlayer(Player* );
        override bool removePlayer(Player* );
        override bool updatePlayer(Player* , std::vector<int> );
        override bool isRunning();
        override bool render(Image[]* );
        override bool update();
        override bool reset();

}
