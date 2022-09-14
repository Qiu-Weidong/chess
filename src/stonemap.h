#ifndef CHESS_STONEMAP_H_
#define CHESS_STONEMAP_H_
#include <array>
#include <stack>
#include "stone.h"
#include "rapidjson/document.h"


class StoneMap {
    
public:
    static const int stone_cnt_ = 32;
    static const int raws_ = 10;
    static const int cols_ = 9;

private:
    struct Step {
        struct { int x, y; } from_;
        struct { int x, y; } to_;
        Stone *mover_;
        Stone *killee_;
        Step(Stone *mover, int from_x, int from_y, int to_x, int to_y, Stone *killee=nullptr) {
            mover_ = mover; killee_ = killee;
            from_.x = from_x; from_.y = from_y;
            to_.x = to_x; to_.y = to_y;
        }

        Step(Stone *mover, int dest_x, int dest_y, Stone *killee=nullptr) {
            assert(mover);
            mover_ = mover;
            from_.x = mover->location_.x;
            from_.y = mover->location_.y;
            to_.x = dest_x;
            to_.y = dest_y;
            killee_ = killee;
        }
    };

    std::stack<Step> steps_;
    Stone *stone_map_[cols_][raws_];
    Stone *selected_stone_;
    Stone stones_[stone_cnt_];

    Stone::StoneColor player_color_;
    Stone::StoneColor turn_;

    void moveStone(Stone *mover, int x, int y);
    void killStone(Stone *killer, int x, int y);

    bool isKingMeeted();

    bool canMove(Stone *mover, int x, int y);
    bool canKingMove(Stone *king, int x, int y);
    bool canMandarinMove(Stone *mandarin, int x, int y);
    bool canBishopMove(Stone *bishop, int x, int y);
    bool canKnightMove(Stone *knight, int x, int y);
    bool canRookMove(Stone *rook, int x, int y);
    bool canCannonMove(Stone *cannon, int x, int y);
    bool canPawnMove(Stone *pawn, int x, int y);

public:
    void init(); // 初始化为开始局面
    void regret(); // 悔棋
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
    void switchTurn() { turn_ = turn_ == Stone::StoneColor::Red ? Stone::StoneColor::Black : Stone::StoneColor::Red; /*selected_stone_ = nullptr;*/ }

    void onBoardClicked(int x, int y) ; // x、y为棋盘坐标
    
    struct { int x, y; } from_, to_;
};

#endif // CHESS_STONEMAP_H_
