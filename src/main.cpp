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
}
