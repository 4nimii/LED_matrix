# LED Matrix

The goal of the project is to create a multiplayer game of pong controller from user's phone and displayed on a shared screen.

Players would be displayed on a circle and move like a classical Pong game to allow a possibly infinite number of players.

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
