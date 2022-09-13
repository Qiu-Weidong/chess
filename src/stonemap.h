#ifndef CHESS_STONEMAP_H_
#define CHESS_STONEMAP_H_
#include <array>
#include "stone.h"
#include "rapidjson/document.h"


class StoneMap {
    
public:
    static const int stone_cnt_ = 32;
    static const int raws = 10;
    static const int cols = 9;

private:
    Stone *stone_map_[cols][raws];
    Stone *selected_stone_;
    Stone stones_[stone_cnt_];

    Stone::StoneColor player_color_;
    Stone::StoneColor turn_;

    
public:
    void init(); // 初始化为开始局面
    Stone &operator[](int x) {
        assert(x >=0 && x < stone_cnt_);
        return stones_[x];
    }

    Stone &get(int x) {
        assert(x >=0 && x < stone_cnt_);
        return stones_[x];
    }

    Stone::StoneColor getPlayerColor() const { return player_color_; }
    Stone::StoneColor getTurn() const { return turn_; }

    Stone *getSelectedStone() const {
        return selected_stone_;
    }

    void setPlayerColor(Stone::StoneColor color) { player_color_ = color; }
    void setTurn(Stone::StoneColor color) { turn_ = color; }
    void switchTurn() { turn_ = turn_ == Stone::StoneColor::Red ? Stone::StoneColor::Black : Stone::StoneColor::Red; }

    void onBoardClicked(int x, int y) ; // x、y为棋盘坐标
    
    struct { int x, y; } from_, to_;
};

#endif // CHESS_STONEMAP_H_
