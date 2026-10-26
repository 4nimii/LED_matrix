#include <vector.h>

#include "game.hpp"


class MainMenu: public Game {

    private:

        std::vector<Player*> players;
        std::vector<int> next_game_vote;
        std::vector<Game*> games;
        std::vector<int> voted_for;
        int current_game;

        int getPlayerIndex(Player* );
        int most_voted_game();

    public:

        MainMenu();
        override bool addPlayer(Player* );
        override bool removePlayer(Player* );
        override bool updatePlayer(Player* , std::vector<int> );
        override bool isRunning();
        override bool render(Image[]* );
        override bool update();
        override bool reset();

}
