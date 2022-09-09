#ifndef CHESS_STONE_H_
#define CHESS_STONE_H_

/*
编号如下图
___________________________________
|00  01  02  03  04  05  06  07  08|   
|                                  |
|    14                      10    |
|15______13______12______11______09|
|            楚河汉界              |
|16￣￣￣18￣￣￣￣19￣￣￣20￣￣￣22|
|    17                      21    |
|                                  | 
|31  30  29  28  27  26  25  24  23|
￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣ 

____________________________________
|00--01--02--03--04--05--06--07--08|   
|----------------------------------|
|----0E----------------------0A----|
|0F------0D------0C------0B------09|
|              river               |
|10------12------13------14------16|
|----11----------------------15----|
|----------------------------------| 
|1F--1E--1D--1C--1B--1A--19--18--17|
￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣
*/


#include "SFML/Graphics.hpp"

class Stone {
    enum class StoneID {
        UpRookLeft  = 0, UpKnightLeft, UpBishopLeft, UpMandarinLeft,
        UpKing, UpMandarinRight, UpBishopRight, UpKnightRight,
        UpRookRight, UpPawnRight, UpCannonRight, UpPawnMidRight,
        UpPawnMiddle, UpPawnMidLeft, UpCannonLeft, UpPawnLeft,
        
        DownPawnLeft, DownCannonLeft, DownPawnMidLeft, DownPawnMiddle,
        DownPawnMidRight, DownCannonRight, DownPawnRight, DownRookRight,
        DownKnightRight, DownBishopRight, DownMandarinRight, DownKing,
        DownMandarinLeft, DownBishopLeft, DownKnightLeft, DownRookLeft
    };

    enum class StoneType {
        King, Mandarin, Bishop, Knight, Rook, Cannon, Pawn
    };

    enum class StoneColor { Red, Black } ;
    enum class UpOrDown { Up, Down };
private:
    StoneType stone_type_;
    bool alive_;
    StoneColor color_;
    UpOrDown up_or_down_;
    sf::Vector2i location_; // 棋盘坐标

    friend class StoneMap;

public:
    sf::Vector2i getLocation() const {
        return location_;
    }

    StoneColor getStoneColor() const {
        return color_;
    }

    UpOrDown getUpOrDown() const {
        return up_or_down_;
    }

    StoneType getStoneType() const {
        return stone_type_;
    }

    bool isAlive() const {
        return alive_;
    }

    void setLoaction(sf::Vector2i location) {
        location_ = location;
    }

    void setAlive(bool alive) {
        alive_ = alive;
    }

    void setColor(StoneColor color) {
        color_ = color;
    }

    void setUpOrDown(UpOrDown up_down) {
        up_or_down_ = up_down;
    }

    void setStoneType(StoneType type) {
        stone_type_ = type;
    }

};


#endif // CHESS_STONE_H_

