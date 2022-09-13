#ifndef CHESS_GAME_H_
#define CHESS_GAME_H_
#include <map>
#include <array>
#include "stonemap.h"
#include "SFML/Graphics.hpp"



class Game
{
private:
    sf::RenderWindow window_;
    
    // map 游戏的主要逻辑
    StoneMap stone_map_;

    sf::Sprite board_, board_background_;
    std::array<sf::Sprite, StoneMap::stone_cnt_> stone_background_, stone_text_;

public:
    Game() ;
    void run();

    void processEvent();
    void render();
};
#endif // CHESS_GAME_H_
