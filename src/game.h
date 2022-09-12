#ifndef CHESS_GAME_H_
#define CHESS_GAME_H_
#include <map>
#include "stonemap.h"
#include "SFML/Graphics.hpp"



class Game
{
private:
    sf::RenderWindow window_;

    std::map<std::string, sf::Texture> textures_; // 用于管理texture资源

    sf::Texture &getTexture(const std::string &url);

    // map 游戏的主要逻辑
    StoneMap stone_map_;
public:
    Game() ;
    void run();

    void processEvent();
    void render();
};
#endif // CHESS_GAME_H_
