#include "SFML/Graphics.hpp"
#include <iostream>
#include <cassert>

int main() {
    const char * title = "中国象棋对战";
    // 尺寸设置
    const int padding_top = 30;
    const int padding_left = 30;
    const int stone_radius = 46;
    const int window_width = stone_radius * 2 * 9 + padding_left * 2;
    const int window_height = stone_radius * 2 * 10 + padding_left * 2;
    const sf::Vector2i window_position(340, 0);

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), sf::String::fromUtf8(title , title+strlen(title)));
    window.setPosition(window_position);
    
    sf::Texture t, bg_texture;
    t.loadFromFile("./resource/img/board.png");
    bg_texture.loadFromFile("./resource/img/bg.jpg");

    sf::Sprite board(t), bg(bg_texture);
    board.setPosition(padding_left + stone_radius, padding_top + stone_radius);
    float scale = stone_radius / 70.0f;
    board.setScale(scale, scale);

    sf::Texture stone_texture;
    stone_texture.loadFromFile("./resource/img/163.png");
    scale = stone_radius / (stone_texture.getSize().x / 2.0);
    sf::Sprite stone(stone_texture);
    stone.setScale(scale, scale);
    stone.setOrigin(stone_texture.getSize().x / 2, stone_texture.getSize().x / 2);
    stone.setPosition(padding_left + stone_radius, padding_top + stone_radius);

    while(window.isOpen()) {
        sf::Event event{};
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) window.close();
        }

        window.clear(sf::Color::Blue);
        window.draw(bg);
        window.draw(board);

        window.draw(stone);
        window.display();
    }
    return 0;
}
/*
棋盘大小
140 * 8 = 1120
140 * 9 = 1260

*/