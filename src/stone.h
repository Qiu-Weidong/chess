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

    friend std::ostream &operator<<(std::ostream &os, const Stone &stone) {
        using StoneType = Stone::StoneType;
        
        std::string content;
        switch(stone.stone_type_) {
            case StoneType::King:
                content = "|  king  |";
                break;
            case StoneType::Bishop:
                content = "| bishop |";
                break;
            case StoneType::Cannon:
                content = "| cannon |";
                break;
            case StoneType::Knight:
                content = "| knight |";
                break;
            case StoneType::Mandarin:
                content = "|mandarin|";
                break;
            case StoneType::Pawn:
                content = "|  pawn  |";
                break;
            case StoneType::Rook:
                content = "|  rook  |";
                break;
            default:
                content = "| unknown|";
                break;
        }

        if(stone.up_or_down_ == Stone::UpOrDown::Up) {
            for(int i=0; i<content.size(); i++) {
                content[i] = toupper(content[i]);
            }
        }
        
        os << content ;
        return os;
    }
};

#endif // CHESS_STONE_H_
