#ifndef CHESS_STONE_H_
#define CHESS_STONE_H_


struct Stone {
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
