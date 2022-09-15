#ifndef CHESS_STONE_H_
#define CHESS_STONE_H_


struct Stone {

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

    ///////////////////////////////////////////////////////////////////////////////////////
    /// @brief 棋子类型
    /// Kind -> 将/帅、Mandarin -> 仕/士、Bishop -> 相/象、Knight->马/傌、
    /// Rook -> 俥/车、Pawn->兵/卒、Cannon->炮/砲
    ///////////////////////////////////////////////////////////////////////////////////////
    enum class StoneType
    {
        King,
        Mandarin,
        Bishop,
        Knight,
        Rook,
        Cannon,
        Pawn
    };

    enum class UpOrDown
    {
        Up,
        Down
    };

    StoneType stone_type_;
    bool alive_;
    UpOrDown up_or_down_;
    struct { int x, y; } location_;
};

#endif // CHESS_STONE_H_
