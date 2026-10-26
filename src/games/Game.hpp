#pragma once
#include <vector>

#include "Player.hpp"
#include "../display/Image.hpp"


/**
 * @class Game
 * @desc Abstract class to define any object which manage players, need to react to player action and render something.
 */
class Game {

    public:

        /**
         * @fn removePlayer
         * @desc Function called to add a player to a running game (e.g. we need to modify the map)
         */
        virtual bool addPlayer(Player* ) = 0;

        /**
         * @fn removePlayer
         * @desc Function called to remove a player to a running game (e.g. we need to modify the map)
         */
        virtual bool removePlayer(Player* ) = 0;

        /**
         * @fn updatePlayer
         * @desc To update player values when a request is received (somewhat MVC)
         */
        virtual bool updatePlayer(Player* , std::vector<int> ) = 0;

        /**
         * @fn isRunning
         * @desc Check if the game is still running
         */
        virtual bool isRunning() = 0;

        /**
         * @fn render
         * @desc Render the current game state to the Image object
         */
        virtual bool render(Image* i) = 0;

        /**
         * @fn update
         * @desc Game loop to update game objects like the ball for Pong
         */
        virtual bool update() = 0;

        /**
         * @fn reset
         * @desc Reset the game to it's default state'
         */
        virtual bool reset() = 0;

};
