#include <fstream>
#include <iostream>
#include "game.h"
#include "settings.h"

int main(int argc, const char **argv)
{
    std::ifstream in;
    if(argc > 1)
        in.open(argv[1]);
    Settings &settings = Settings::getInstance();
    if(in.is_open()) settings.loadFromFile(in);
    
    Game().run();
    return 0;

    // sf::Image img;
    // img.loadFromFile("./resource/raw/river.jpg");

    // for(int i=0; i<img.getSize().x; i++) {
    //     for(int j=0; j<img.getSize().y; j++) {
    //         int t = img.getPixel(i, j).toInteger();
    //         if(t < 0) img.setPixel(i, j, sf::Color::Transparent);
    //         else img.setPixel(i, j, sf::Color::White);
    //     }
    // }
    // img.saveToFile("./resource/tmp.png");
}
