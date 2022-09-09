#include <fstream>
#include <iostream>
#include "game.h"

int main(int argc, const char **argv)
{
    std::ifstream in;
    if(argc > 1)
        in.open(argv[1]);
    
    if(! in.is_open()) {
        std::cerr << "can\'t open settings.jsonc" << std::endl;
    }

    Game game;
    game.initFromFile(in);
    game.run();
    return 0;
}
