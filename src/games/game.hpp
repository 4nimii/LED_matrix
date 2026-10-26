/*
 * Mother class of all the Games to provide the same basic access to all of them.
 *
 *
 *
 *
 *
 */

class Game {

    Game();
    bool addPlayer(Player* );
    bool removePlayer(Player* );
    // Update player in-game values
    bool updatePlayer(Player* , std::vector<int> );
    bool isRunning();
    bool render(Image[]* );



}
