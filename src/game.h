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

    sf::Sprite board_, board_background_, box_select_, box_from_, box_to_;
    std::array<sf::Sprite, StoneMap::stone_cnt_> stone_background_, stone_text_;
    sf::Sprite turn_label_background_, turn_label_red_, turn_label_black_;
    sf::Sprite river_;
    sf::Text new_game_button_, undo_button_;

    void mouseClickedHandler(const sf::Event &event);

    void mouseMoveHandler(const sf::Event &event);

    void openNewGame();

    void updateStones();
public:
    Game() ;
    void run();

    void processEvent();
    void render();
};
#endif // CHESS_GAME_H_
