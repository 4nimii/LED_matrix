# Game core

The game core is the layer with manage each players, win and loss conditions and start/end states. The basic rules of Pong are:
- If a player send the ball to the goal of a opponent, its score is increased by one
- If the ball touch the goal, all the players and the ball position are reset to their starting position. 

The game rendering part take the game core and display it in a NxM pixel matrix, NxM being more an aspect ratio than a the final resolution. It abstract rendering process and give more flexibility on how and where the final pixel data are displayed.

## Core

It should handle:
- Player joining and leaving
- Player movement
- Ball movement
- Win/loss
- Start/end

### Player

Players have:
- a name
- a position
- a linked IP/ID for connected device
- a score

And maybe even:
- a Color/Appearance
- a Trail/effects

A player can:
- Update their position
- Change their name
- Interact with the ball

### Ball

The ball have:
- a position
- a direction

The ball can:
- Update it's position given it's direction
- It's direction can change given iteration with player
- Interact with the player

### Game

The game have:
- A start/end state
- A list of players
- A ball

The game can:
- Check for interaction between the ball and a player
- Update the position of the ball and players
- Delete a player dynamically
- Prevent player from joining after game start
- Control it's start/end state
- Manage scores

## Rendering

The rendering part take the game core part and create a pixel matrix from it.

It should:
- Take abstract player's and ball's position and convert them to pixel values
- Display the ball and player in the matrix at the correct position
- Output a NxM matrix of values representing the current state of the game
- Display a start/end screen

## Pseudo-code e.g.

```cpp
class Player {
  std::string name;
  std::string ip/id;
  int[2] position;
  uint score;

  void update_position();
  void update_name();
}

class Ball {
  int[2] position;
  float[2] direction;
}

class Game {
  vector<Player> players;
  bool started;
  bool ended;
  Ball ball;

  void update();
  void add_player(Player);
  void remove_player(ID/IP);
  void start();
}

typedef struct Image {
  vector<vector<uint16_m>> data
  Image(n, m);
} 

Image render_matrix(Game);
```
