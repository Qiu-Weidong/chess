#ifndef CHESS_STONEMAP_H_
#define CHESS_STONEMAP_H_
#include <array>
#include <stack>
#include <array>
#include <vector>
#include <iostream>
#include "stone.h"
#include "step.h"


class StoneMap {
    
public:
    static const int stone_cnt_ = 32;
    static const int raws_ = 10;
    static const int cols_ = 9;
    
    using StoneArray = std::array<Stone, stone_cnt_>;
    ////////////////////////////////////////////////////////////////////////////////////
    /// \brief 用于对棋子进行编号
    /// ____________________________________        ___________________________________
    /// |00--01--02--03--04--05--06--07--08|        |00  01  02  03  04  05  06  07  08|
    /// |----------------------------------|        |                                  |
    /// |----0E----------------------0A----|        |    14                      10    |
    /// |0F------0D------0C------0B------09|        |15______13______12______11______09|
    /// |              river               |        |            楚河汉界               |
    /// |10------12------13------14------16|        |16￣￣￣18￣￣￣￣19￣￣￣20￣￣￣22|
    /// |----11----------------------15----|        |    17                      21    |
    /// |----------------------------------|        |                                  |
    /// |1F--1E--1D--1C--1B--1A--19--18--17|        |31  30  29  28  27  26  25  24  23|
    /// ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣         ￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣￣
    /////////////////////////////////////////////////////////////////////////////////////
    enum class StoneID
    {
        UpRookLeft = 0,
        UpKnightLeft,
        UpBishopLeft,
        UpMandarinLeft,
        UpKing,
        UpMandarinRight,
        UpBishopRight,
        UpKnightRight,
        UpRookRight,
        UpPawnRight,
        UpCannonRight,
        UpPawnMidRight,
        UpPawnMiddle,
        UpPawnMidLeft,
        UpCannonLeft,
        UpPawnLeft,

        DownPawnLeft,
        DownCannonLeft,
        DownPawnMidLeft,
        DownPawnMiddle,
        DownPawnMidRight,
        DownCannonRight,
        DownPawnRight,
        DownRookRight,
        DownKnightRight,
        DownBishopRight,
        DownMandarinRight,
        DownKing,
        DownMandarinLeft,
        DownBishopLeft,
        DownKnightLeft,
        DownRookLeft,
        
        None = -1,
    };

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

    StoneMap(StoneMap &&) = delete;
    StoneMap &operator=(StoneMap &&) = delete;
    StoneMap(const StoneMap &map) = delete;
    
    void generatePossibleStoneSteps(Stone &stone, std::vector<Step> &steps);
    void generatePossibleKingSteps(Stone &king, std::vector<Step> &steps) ;
    void generatePossibleMandarinSteps(Stone &mandarin, std::vector<Step> &steps) ;
    void generatePossibleBishopSteps(Stone &bishop, std::vector<Step> &steps) ;
    void generatePossibleKnightSteps(Stone &knight, std::vector<Step> &steps) ;
    void generatePossibleRookSteps(Stone &rook, std::vector<Step> &steps) ;
    void generatePossibleCannonSteps(Stone &cannon, std::vector<Step> &steps) ;
    void generatePossiblePawnSteps(Stone &pawn, std::vector<Step> &steps) ;
    void generatePossibleRookOrCannonSteps(Stone &stone, std::vector<Step> &steps);
    void generatePossibleKingOrPawnSteps(Stone &stone, std::vector<Step> &steps);
    
    inline void clearStoneMap() {
        for(int i=0; i<cols_; i++) {
            for(int j=0; j<raws_; j++) stone_map_[i][j] = nullptr;
        }
    }
    
public:
    StoneMap() = default;
    StoneMap &operator=(const StoneMap &map) ;
    
    Stone &operator[](int index) {
        assert(index >=0 && index < stone_cnt_);
        return stones_[index];
    }

    Stone &operator[](StoneID id) {
        return stones_[(int)id];
    }

    Stone &get(int index) {
        assert(index >= index && index < stone_cnt_);
        return stones_[index];
    }

    Stone &get(StoneID id) { return stones_[(int)id]; }

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



    std::vector<Step> generatePossibleSteps() ;
    int evaluate() const;
    void init(Stone::UpOrDown turn = Stone::UpOrDown::Down); // 初始化为开始局面
    void makeMove(const Step &step);
    void revokeMove(const Step &step);
    bool canMove(const Step &step);

    friend std::ostream &operator<<(std::ostream &os, const StoneMap &map) {
        os << "__________________________________________________________________________________________\n";
        for(int j=0; j<StoneMap::raws_; j++) {
            for(int i=0; i<StoneMap::cols_; i++) {
                if(map.stone_map_[i][j] == nullptr) os << "|        |";
                else os << *map.stone_map_[i][j];
            }
            os << std::endl;
        }
        os << "------------------------------------------------------------------------------------------\n";
        return os;
    }
};

#endif // CHESS_STONEMAP_H_
