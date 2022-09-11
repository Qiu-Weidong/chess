#include "stonemap.h"

void StoneMap::init()
{
    sf::Vector2i locations[] = {
        sf::Vector2i(0, 0),
        sf::Vector2i(1, 0),
        sf::Vector2i(2, 0),
        sf::Vector2i(3, 0),
        sf::Vector2i(4, 0),
        sf::Vector2i(5, 0),
        sf::Vector2i(6, 0),
        sf::Vector2i(7, 0),
        sf::Vector2i(8, 0),
        sf::Vector2i(8, 3),
        sf::Vector2i(7, 2),
        sf::Vector2i(6, 3),
        sf::Vector2i(4, 3),
        sf::Vector2i(2, 3),
        sf::Vector2i(1, 2),
        sf::Vector2i(0, 3),

        sf::Vector2i(0, 6),
        sf::Vector2i(1, 7),
        sf::Vector2i(2, 6),
        sf::Vector2i(4, 6),
        sf::Vector2i(6, 6),
        sf::Vector2i(7, 7),
        sf::Vector2i(8, 6),
        sf::Vector2i(8, 9),
        sf::Vector2i(7, 9),
        sf::Vector2i(6, 9),
        sf::Vector2i(5, 9),
        sf::Vector2i(4, 9),
        sf::Vector2i(3, 9),
        sf::Vector2i(2, 9),
        sf::Vector2i(1, 9),
        sf::Vector2i(0, 9),
    };
    Stone::StoneType types[] = {
        Stone::StoneType::Rook, Stone::StoneType::Knight, Stone::StoneType::Bishop, Stone::StoneType::Mandarin,
        Stone::StoneType::King, Stone::StoneType::Mandarin, Stone::StoneType::Bishop, Stone::StoneType::Knight,
        Stone::StoneType::Rook, Stone::StoneType::Pawn, Stone::StoneType::Cannon, Stone::StoneType::Pawn,
        Stone::StoneType::Pawn, Stone::StoneType::Pawn, Stone::StoneType::Cannon, Stone::StoneType::Pawn,

        Stone::StoneType::Pawn, Stone::StoneType::Cannon, Stone::StoneType::Pawn, Stone::StoneType::Pawn, 
        Stone::StoneType::Pawn, Stone::StoneType::Cannon, Stone::StoneType::Pawn, Stone::StoneType::Rook, 
        Stone::StoneType::Knight, Stone::StoneType::Bishop, Stone::StoneType::Mandarin, Stone::StoneType::King, 
        Stone::StoneType::Mandarin, Stone::StoneType::Bishop, Stone::StoneType::Knight, Stone::StoneType::Rook,
    };
    
    memset(stone_map_, 0, sizeof(stone_map_));
    for (int id = 0; id <= stone_cnt_; id++)
    {
        stones_[id].up_or_down_ = id < (int)Stone::StoneID::DownPawnLeft ? Stone::UpOrDown::Up : Stone::UpOrDown::Down;
        stones_[id].alive_ = true;
        stones_[id].color_ = id < (int)Stone::StoneID::DownPawnLeft ? Stone::StoneColor::Black : Stone::StoneColor::Red;
        stones_[id].location_ = locations[id];
        stones_[id].stone_type_ = types[id];

        int x = locations[id].x;
        int y = locations[id].y;

        stone_map_[x][y] = &stones_[id];
    }

    

}

