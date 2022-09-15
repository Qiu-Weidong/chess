#include <fstream>
#include "settings.h"
#include "app.h"

int main(int argc, const char **argv)
{
    std::ifstream in;
    if(argc > 1)
        in.open(argv[1]);
    Settings &settings = Settings::getInstance();
    if(in.is_open()) settings.loadFromFile(in);
    
    return App().exec();

    // // int abc = 185;
    // sf::Image img;
    // img.loadFromFile("./resource/img/win/win6.png");

    // for(int i=0; i<img.getSize().x; i++) {
    //     for(int j=0; j<img.getSize().y; j++) {
    //         if(img.getPixel(i, j) != sf::Color::Transparent) img.setPixel(i, j, sf::Color::White);
    //     }
    // }

    // img.saveToFile("./resource/tmp.png");
}
// 246 246 246