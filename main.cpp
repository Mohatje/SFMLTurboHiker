#include "./src/Display/Game.h"


int main() {

    turbohikerSFML::Game game("./Config/config.ini");
    game.run();


    return EXIT_SUCCESS;
}
