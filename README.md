# LED Matrix

The goal of the project is to use a LED display to display things.

Currently we have:

- A base project structure with:
  - Some kind of rendering pipeline
  - A game object
  - A main menu to manage each games
- What we need is:
  - Make an actual game and add it to the main menu
  - Implement font rendering with the lib. [Schrift](https://tomolt.github.io/libschrift/v0.10.2.schrift.3.html) (in include)
  - Implement network managment/player managment with a Network object and [CrowCpp](https://crowcpp.org/master/) (in include)
  - Add display driver for our LED display
  - It would be cool to have a Util folder with convenience functions/Macros like RGB() or HSL() to be able to write RGB/HSL color code in the program and directly convert them to uint8_t (or maybe uint16_t in the future)
- What we can do right now is:
  - Start the Main menu
  - Use the main menu to render something on the Image object
  - Display the image object with a display driver
  
```mermaid
classDiagram
class Game {
        bool addPlayer(Player* )
        bool removePlayer(Player* )
        bool updatePlayer(Player* , std::vector<int> )
        bool isRunning()
        bool render(Image* i)
        bool update()
        bool reset()
}

class MainMenu {

        std::vector<Player*> players
        std::vector<int> next_game_vote
        std::vector<Game*> games
        std::vector<int> voted_for
        int current_game

        int getPlayerIndex(Player* )
        int mostVotedGame()
        MainMenu(std::vector<Game*> games)

}

class Player {

        std::string name;
        std::string id;
        Player(std::string name, std::string id);
        std::string getID();

}

class Image {

        int size_x;
        int size_y;
        std::vector<uint8_t> pixels;
        uint8_t drawing_color;
        float view_unit_x;
        float view_unit_y;

        Image(int size_x, int size_y);
        uint8_t getPixelAt(int x, int y);
        bool setPixelAt(int x, int y);
        bool setDrawingColor(uint8_t color);
        bool clear();
        float weigthUnit();
        float heigthUnit();
        bool drawGlyph(std::string glyph, float vw, float vh);
        bool drawText(std::string text, float vw, float vh);
        bool drawRect(float vw, float vh, float weight, float height);
        bool drawCircle(float vw, float vh, float radius);
        bool drawTriangle(float vw1, float vh1, float vw2, float vh2, float vw3, float vh3);

}

class Display {

        virtual bool display(Image* ) = 0;
        virtual ~Display() = default;

}

class Stdout {

        ~Stdout() = default;

}

class Sdl {

        int size_x;
        int size_y;
        SDL_Event event;
        SDL_Renderer* renderer;
        SDL_Window* window;

        Sdl(int x, int y);
        ~Sdl();

}

MainMenu --|> Game
MainMenu "*" *-- "*"  Player
Stdout --|> Display
Sdl --|> Display

Game .. Image
Display .. Image
```
