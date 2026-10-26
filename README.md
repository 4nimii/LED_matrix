# LED Matrix

The goal of the project is to create a multiplayer game of pong controller from user's phone and displayed on a shared screen.

Players would be displayed on a circle and move like a classical Pong game to allow a possibly infinite number of players.

## Base game idea

When the microC is plug in, the Wi-Fi chip is powered along with the DHCP service to allow connection to the network and auto assign IPs, then our program is started, start an HTTP server to accept incoming requests and deliver the web page to control the pong paddle assigned to the player. 

The game would display players in a circle, but each player would look and move like in a actual pong game. For instance, when two players are connected, they would be facing each other as in classical Pong, when three players are connected, they would be displayed as a triangle, with four players a square and so on and so forth. When a player connected or disconnect from the game (Wi-Fi) it would automatically change the configuration of the circle and place the players on the new increased or decreased configuration.

When a player touch the ball and send it out of the "board", a point it granted to them, a point could also be removed to player player who own the "board" part where the ball escaped from (i.e. the player who missed missed the ball).

A special mode could be created for the case when only one player is playing.

The web UI could be really simple, with a slider to control the player position and maybe some cosmetic options like player name, color, and ball trail to give to the ball after touching it.

Post-processing effects could be applied on the final render to add for instance deformation from ball impact depending of its speed (e.g. wave effect, etc). 

## Material

- Micro-controller (any ?)
- Screen (any ?)

## Tasks

### Network & dev. web

Work on how to transmit data from phones to the microC and how to display the controls/how to input them on the phone's browser

### Game core

Work on how to manage the core gae mechanic, like player movement, player managment, lose/win states, etc

### Display

Work on how to display the game on (a/any ?) screen.

Example pseudo code game loop could be (without network/player interaction update):

```cpp
void main() {
  Image *screen(128, 64);
  Game core();
  Player p1();
  Player p2();
  core.add_player(p1);
  core.add_player(p2);
  Display d("screen 1");
  core.start()
  while(1) {
    core.update();
    render(screen);
    d.display(screen);
  }
}
```
