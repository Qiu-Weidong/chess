#include "SFML/Graphics.hpp"
#include <iostream>
#include <cassert>

int main(int argc, const char **argv)
{
    // const std::string base_path = "./resource/img/stone-bg/";
    // const char *title = "中国象棋对战";
    // // 尺寸设置
    // const int padding_top = 30;
    // const int padding_left = 30;
    // const int stone_radius = 46;
    // const int window_width = stone_radius * 2 * 9 + padding_left * 2;
    // const int window_height = stone_radius * 2 * 10 + padding_left * 2;
    // const sf::Vector2i window_position(340, 0);

    // sf::RenderWindow window(sf::VideoMode(window_width, window_height), sf::String::fromUtf8(title, title + strlen(title)));
    // window.setPosition(window_position);

    // sf::Texture t, bg_texture, text_texture;
    // t.loadFromFile("./resource/img/board.png");
    // bg_texture.loadFromFile("./resource/img/bg.jpg");
    // text_texture.loadFromFile("./resource/img/jinwen.png");

    // sf::Sprite board(t), bg(bg_texture), text(text_texture);
    // board.setPosition(padding_left + stone_radius, padding_top + stone_radius);
    // float scale = stone_radius / 70.0f;
    // board.setScale(scale, scale);

    // sf::Texture stone_texture;
    // if(argc <= 1)
    //     stone_texture.loadFromFile("./resource/img/3.png");
    // else stone_texture.loadFromFile(base_path + argv[1] + ".png");

    // scale = stone_radius / (stone_texture.getSize().x / 2.0);
    // const int circle_radius = stone_radius - 6;
    // sf::CircleShape circle(circle_radius);
    // circle.setOutlineThickness(3);
    // circle.setOutlineColor(sf::Color::Red);
    // circle.setFillColor(sf::Color::Transparent);

    // sf::Sprite stone(stone_texture);
    // stone.setScale(scale, scale);
    // stone.setOrigin(stone_texture.getSize().x / 2.0, stone_texture.getSize().y / 2.0);

    // circle.setOrigin(circle_radius , circle_radius );
    // stone.setPosition(padding_left + stone_radius, padding_top + stone_radius);
    // circle.setPosition(padding_left + stone_radius, padding_top + stone_radius);


    // text.setTextureRect(sf::IntRect(0, 157, 121, 157));
    // // text.setOrigin(121 / 2.0, 157 / 2.0);
    // text.setPosition(padding_left + stone_radius, padding_top + stone_radius);
    // text.setColor(sf::Color::Red);
    // while (window.isOpen())
    // {
    //     sf::Event event{};
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }

    //     window.clear();
    //     window.draw(bg);
    //     window.draw(board);

    //     window.draw(stone);
    //     window.draw(circle);
    //     window.draw(text);
    //     window.display();
    // }
    
    // const std::string base = "./resource/raw/";
    // const std::string name = base + (argc > 1 ? argv[1] : "kaiti") ;
    // sf::Image img;
    // img.loadFromFile(name + ".jpg");
    // int x = img.getSize().x;
    // int y = img.getSize().y;


    // for(int i=0; i<x; i++) {
    //     for(int j=0; j<y; j++) {
    //         if(img.getPixel(i, j) != sf::Color::Black) {
    //             img.setPixel(i, j, sf::Color::Transparent);
    //         }
    //         else {
    //             img.setPixel(i, j, sf::Color::White);
    //         }
    //     }
    // }
    // img.saveToFile(name+".png");

    return 0;
}

/*
棋盘大小
140 * 8 = 1120
140 * 9 = 1260

1560 * 780 r = 156 10*5;
72 大约121 315/2=157
*/


// sf::Color pixels[156][156*50];
// int main(int argc, const char **argv)
// {
//     std::cout << "what happened!" << std::endl;
    
//     sf::Image img;
//     const std::string base_name = "./resource/img/stone-bg/";
//     std::cout << "fuck";
//     for(int i=0; i<50; i++) {
//         img.loadFromFile(base_name + std::to_string(i)+".png");
//         // 将img拷贝到pixels的对应位置

//         for(int j=0; j<156; j++) {
//             for(int k=0; k<156; k++) {
//                 pixels[i*156 +j][ k] = img.getPixel(j, k);
//             }
//         }
//     }

//     img.create(156, 156*50, (sf::Uint8 *)pixels);
//     img.saveToFile("./resource/img/stone-bg/all.png");

//     // std::cout << "hello world!" << std::endl;
//     return 0;
// }



// #include "SFML/Graphics.hpp"
// #include <iostream>
// #include <cassert>

// sf::Color pixels[156*50][156];

// void foo(const sf::Image &img, int x, int y)
// {
//     // x是列, y是行
//     int cnt = x * 5 + y;
//     const int r = 156 >> 1;
//     // std::cout << "cnt=" << cnt << std::endl;

//     for (int i = 0; i < 156; i++)
//     {
//         for (int j = 0; j < 156; j++)
//         {
//             // assert(x*156+i < img.getSize().y);
//             // assert(y*156+j < img.getSize().x);
//             if((i-r)*(i-r)+(j-r)*(j-r) > r*r)
//                 pixels[cnt*156+i][j] = sf::Color::Transparent;
//             else
//             pixels[cnt*156+i][j] = img.getPixel(x*156+i, y*156+j);
//         }
//     }
// }

// int main(int argc, const char **argv)
// {
//     sf::Image img;
//     img.loadFromFile("./resource/raw/wood_peeling_paint_weathered.jpg");
//     std::cout << "fucker" << std::endl;
//     std::cout << img.getSize().x << ", " << img.getSize().y << std::endl; // 1560 780
//     for (int i = 0; i < 10; i++)
//     {
        
//         for (int j = 0; j < 5; j++)
//         {
//             // std::cout << "i=" << i << ", j= " << j << std::endl;
//             foo(img, i, j);
//         }
//     }
//     std::cout << "shit" << std::endl;
//     img.create(156, 156*50, (sf::Uint8 *)pixels);
//     img.saveToFile("./resource/raw/all.png");
//     return 0;
// }


    // sf::Image img;
    // img.loadFromFile("./resource/raw/jinwen.png");

    // int x = img.getSize().x;
    // int y = img.getSize().y;

    // for(int i=0; i<x; i++) {
    //     for(int j=0; j<y; j++) {
    //         int t = img.getPixel(i, j).toInteger();
    //         if(t > 0) {
    //             img.setPixel(i, j, sf::Color::White);
    //         }
    //         else {
    //             img.setPixel(i, j, sf::Color::Transparent);
    //         }
    //     }
    // }
    // // img.createMaskFromColor(sf::Color::White);

    // img.saveToFile("./resource/jinwen.png");