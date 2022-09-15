#ifndef CHESS_STONEMAP_H_
#define CHESS_STONEMAP_H_
#include <array>
#include <stack>
#include <array>
#include "stone.h"
#include "step.h"


class StoneMap {
    
public:
    static const int stone_cnt_ = 32;
    static const int raws_ = 10;
    static const int cols_ = 9;
    
    using StoneArray = std::array<Stone, stone_cnt_>;
private:
    Stone *stone_map_[cols_][raws_];
    StoneArray stones_;
    Stone::UpOrDown turn_;
    
    bool isKingMeeted();
    bool canKingMove(const Step &step);
    bool canMandarinMove(const Step &step);
    bool canBishopMove(const Step &step);
    bool canKnightMove(const Step &step);
    bool canRookMove(const Step &step);
    bool canCannonMove(const Step &step);
    bool canPawnMove(const Step &step);

public:
    void init(Stone::UpOrDown turn = Stone::UpOrDown::Down); // 初始化为开始局面
    
    void makeMove(const Step &step);
    void revokeMove(const Step &step);
    bool canMove(const Step &step);

    Stone &operator[](int index) {
        assert(index >=0 && index < stone_cnt_);
        return stones_[index];
    }

    Stone &operator[](Stone::StoneID id) {
        return stones_[(int)id];
    }

    Stone &get(int index) {
        assert(index >= index && index < stone_cnt_);
        return stones_[index];
    }

    Stone &get(Stone::StoneID id) { return stones_[(int)id]; }

    Stone *getStoneOnMap(int x, int y) const {
        if(x < 0 || x > cols_ || y < 0 || y > raws_) return nullptr;
        else return stone_map_[x][y];
    }

    const StoneArray &getAllStones() const {
        return stones_;
    }

    void setTurn(Stone::UpOrDown turn) { turn_ = turn; }
    Stone::UpOrDown getTurn() const { return turn_; }
    void switchTurn() { turn_ = turn_ == Stone::UpOrDown::Up ? Stone::UpOrDown::Down : Stone::UpOrDown::Up; }

    friend class ComputerPlayer;
};

#endif // CHESS_STONEMAP_H_
