#include <string>

class Player {

    private:

        std::string name;
        std::string id;

    public:

        // Name is set once, ID could be IP, etc
        Player(std::string name, std::string id);

        /**
         * @fn gtID
         * @desc Return the player ID, could also preprocess it too like merge other info and things.
         */
        std::string getID();

}
