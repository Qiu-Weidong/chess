#ifndef CHESS_GAME_H_
#define CHESS_GAME_H_
#include <fstream>
#include <map>
#include "SFML/Graphics.hpp"


class Game
{
private:
    sf::RenderWindow window_;

    std::map<std::string, sf::Texture> textures_; // 用于管理texture资源

    // Sprite
    sf::Sprite board_, board_background_;

    // 保存一下相关尺寸设置，计算棋子的坐标的时候要用
    int padding_left_;
    int padding_right_;
    int padding_top_;
    int padding_bottom_;
    int stone_radius_;

    sf::Texture &getTexture(const std::string &url);

public:
    void initFromFile(std::ifstream &in);
    void run();

    void processEvent();
    void render();
};
#endif // CHESS_GAME_H_
