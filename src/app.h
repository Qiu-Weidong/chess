#ifndef CHESS_APP_H_
#define CHESS_APP_H_
#include <array>
#include "game.h"
#include "SFML/Graphics.hpp"


class App {
private:
    sf::RenderWindow window_;

    sf::Sprite board_, board_background_, box_select_, box_from_, box_to_;
    std::array<sf::Sprite, StoneMap::stone_cnt_> stone_background_, stone_text_;
    sf::Sprite turn_label_background_, turn_label_red_, turn_label_black_;
    sf::Sprite river_;

    sf::Sprite looog_, win_, loose_;
    sf::Text new_game_button_, undo_button_;
    
    Game game_;
    
    void processEvent();
    void update();
    void render();

    void mouseClickedHandler(sf::Event &event);
    void mouseMovedHandler(sf::Event &event);

    App(const App &) = delete;
    App(App &&) = delete;
    App &operator=(const App &) = delete;
    App &operator=(App &&) = delete;
public:
    App();
    int exec();

};
#endif // CHESS_APP_H_
