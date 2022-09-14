#include "stonemap.h"
#include "settings.h"
#include "asset.h"


void StoneMap::init()
{  
    memset(stone_map_, 0, sizeof(stone_map_));
    Settings &settings = Settings::getInstance();

    while(! steps_.empty()) steps_.pop();

    int locationx[] = {
        0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 7, 6, 4, 2, 1, 0,
        0, 1, 2, 4, 6, 7, 8, 8, 7, 6, 5, 4, 3, 2, 1, 0,
    };

    int locationy[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 3, 3, 3, 2, 3,
        6, 7, 6, 6, 6, 7, 6, 9, 9, 9, 9, 9, 9, 9, 9, 9,
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

    Stone::StoneColor user, computor;
    if(settings.choose_red_) {
        player_color_ = Stone::StoneColor::Red;
        user = Stone::StoneColor::Red;
        computor = Stone::StoneColor::Black;
    }
    else {
        player_color_ = Stone::StoneColor::Black;
        user = Stone::StoneColor::Black;
        computor = Stone::StoneColor::Red;
    }

    for(int i=0; i<stone_cnt_; i++) {
        stones_[i].up_or_down_ = i < (int)Stone::StoneID::DownPawnLeft ? Stone::UpOrDown::Up : Stone::UpOrDown::Down;
        stones_[i].alive_ = true;
        
        int x = locationx[i], y = locationy[i];
        stones_[i].location_.x = x;
        stones_[i].location_.y = y;
        stones_[i].stone_type_ = types[i];

        stones_[i].color_ = i < (int)Stone::StoneID::DownPawnLeft ? computor : user;

        stone_map_[x][y] = &stones_[i];
    }

    turn_ = Stone::StoneColor::Red;
    selected_stone_ = nullptr;

    to_.x = to_.y = from_.x = from_.y = -2;

}

void StoneMap::onBoardClicked(int x, int y) {
    assert(x >=0 && x <= 8 && y >= 0 && y <= 9);
    if(selected_stone_ == nullptr) {
        // 选择一个棋子
        if(stone_map_[x][y] != nullptr && stone_map_[x][y]->color_ == turn_) {
            // 选择了己方棋子
            selected_stone_ = stone_map_[x][y];
        }
        from_.x = from_.y = to_.x = to_.y = -2;
    }
    else {
        assert(selected_stone_->color_ == turn_);
        if(stone_map_[x][y] != nullptr) {
            // 吃子或重新选择棋子
            if(stone_map_[x][y]->color_ == turn_) {
                // 重新选择棋子
                selected_stone_ = stone_map_[x][y];
                from_.x = from_.y = to_.x = to_.y = -2;
            }
            else {
                // 吃子
                if(canMove(selected_stone_, x, y)) {

                    steps_.push(Step(selected_stone_, x, y, stone_map_[x][y]));
                    
                    killStone(selected_stone_, x, y);
                    switchTurn();
                }
                else {
                    
                    from_.x = from_.y = to_.x = to_.y = -2;
                }
                selected_stone_ = nullptr;
            }
        }
        else {
            // 移动
            if(canMove(selected_stone_, x, y)) {
                steps_.push(Step(selected_stone_, x, y));
                
                moveStone(selected_stone_, x, y);
                switchTurn();
            }
            else {                    
                from_.x = from_.y = to_.x = to_.y = -2;
            }
            selected_stone_ = nullptr;
        }
    }
}

void StoneMap::moveStone(Stone *mover, int x, int y) {
    assert(mover);
    assert(stone_map_[x][y] == nullptr); // 确保目标位置没有棋子
    int from_x = mover->location_.x;
    int from_y = mover->location_.y;
    assert(stone_map_[from_x][from_y] == mover);
    
    // 原来的位置已经没有这个棋子了
    stone_map_[from_x][from_y] = nullptr;

    stone_map_[x][y] = mover;
    mover->location_.x = x;
    mover->location_.y = y;

    from_.x = from_x;
    from_.y = from_y;
    to_.x = x;
    to_.y = y;
}

void StoneMap::killStone(Stone *killer, int x, int y) {
    assert(killer);
    assert(stone_map_[x][y] != nullptr);
    assert(stone_map_[x][y]->color_ != killer->color_);

    Stone *killee = stone_map_[x][y];
    killee->alive_ = false;
    stone_map_[x][y] = nullptr;

    moveStone(killer, x, y);
}

bool StoneMap::canMove(Stone *mover, int x, int y) {
    if(! mover || x < 0 || x > 8 || y < 0 || y > 9 || 
        stone_map_[x][y] != nullptr && stone_map_[x][y]->color_ == mover->color_ ||
        mover->location_.x == x && mover->location_.y == y) return false;

    bool ret = true;
    switch(mover->stone_type_) {
        case Stone::StoneType::King:
            ret = canKingMove(mover, x, y);
            break;
        case Stone::StoneType::Mandarin:
            ret = canMandarinMove(mover, x, y);
            break;
        case Stone::StoneType::Bishop:
            ret = canBishopMove(mover, x, y);
            break;
        case Stone::StoneType::Knight:
            ret = canKnightMove(mover, x, y);
            break;
        case Stone::StoneType::Rook:
            ret = canRookMove(mover, x, y);
            break;
        case Stone::StoneType::Cannon:
            ret = canCannonMove(mover, x, y);
            break;
        case Stone::StoneType::Pawn:
            ret = canPawnMove(mover, x, y);
            break;
        default:
            ret = false;
            break;
    }
    
    if(! ret) return ret;
    
    // 先尝试移动，然后复位
    Stone *dest = stone_map_[x][y];
    int from_x = mover->location_.x, from_y = mover->location_.y;

    assert(! dest || dest->alive_);
    ! dest ? moveStone(mover, x, y) : killStone(mover, x, y);

    // 检查将帅碰面
    ret = ! isKingMeeted();

    // 恢复
    stone_map_[from_x][from_y] = mover;
    mover->location_.x = from_x;
    mover->location_.y = from_y;
    stone_map_[x][y] = dest;
    if(dest) dest->alive_ = true;

    return ret;

    
}

bool StoneMap::isKingMeeted() {
    Stone &up_king = stones_[(int)Stone::StoneID::UpKing];
    Stone &down_king = stones_[(int)Stone::StoneID::DownKing];

    // assert(up_king.alive_ && down_king.alive_);
    if(! up_king.alive_ || ! down_king.alive_) return false;

    if(up_king.location_.x != down_king.location_.x) return false;
    int x = up_king.location_.x;
    for(int y = up_king.location_.y+1; y < down_king.location_.y; y++) 
    {
        if(stone_map_[x][y] != nullptr) return false;
    }
    return true;
}

bool StoneMap::canKingMove(Stone *king, int x, int y) {
    if(x < 3 || x > 5 || 
        king->up_or_down_ == Stone::UpOrDown::Up && y > 2 ||
        king->up_or_down_ == Stone::UpOrDown::Down && y < 7) return false;
    else return ((king->location_.x - x) * (king->location_.x - x) + 
        (king->location_.y - y) * (king->location_.y - y) == 1) ;
}
bool StoneMap::canMandarinMove(Stone *mandarin, int x, int y) {
    if(x < 3 || x > 5 || 
        mandarin->up_or_down_ == Stone::UpOrDown::Up && y > 2 ||
        mandarin->up_or_down_ == Stone::UpOrDown::Down && y < 7) return false;
    else return ((mandarin->location_.x - x) * (mandarin->location_.x - x) + 
        (mandarin->location_.y - y) * (mandarin->location_.y - y) == 2) ;
}
bool StoneMap::canBishopMove(Stone *bishop, int x, int y) {
    if(bishop->up_or_down_ == Stone::UpOrDown::Up && y > 4 ||
        bishop->up_or_down_ == Stone::UpOrDown::Down && y < 5 || 
        (bishop->location_.x - x) * (bishop->location_.x - x) + 
        (bishop->location_.y - y) * (bishop->location_.y - y) != 8) 
        return false;
    int cx = (bishop->location_.x + x) / 2;
    int cy = (bishop->location_.y + y) / 2;
    return ! stone_map_[cx][cy] ;
}
bool StoneMap::canKnightMove(Stone *knight, int x, int y) {
    if ((knight->location_.x - x) * (knight->location_.x - x) + 
        (knight->location_.y - y) * (knight->location_.y - y) != 5) 
        return false;
    else if((knight->location_.x - x) * (knight->location_.x - x) == 1) {
        int cx = knight->location_.x;
        int cy = (knight->location_.y + y) / 2;
        return ! stone_map_[cx][cy]; 
    }
    else {
        int cx = (knight->location_.x + x) / 2;
        int cy = knight->location_.y;
        return ! stone_map_[cx][cy]; 
    }
}
bool StoneMap::canRookMove(Stone *rook, int x, int y) {
    if(rook->location_.x == x) {
        assert(rook->location_.y != y);
        int miny = rook->location_.y < y ? rook->location_.y : y;
        int maxy = rook->location_.y > y ? rook->location_.y : y;
        for(y = miny+1; y<maxy; y++) {
            if(stone_map_[x][y]) return false;
        }
        return true;
    }
    else if(rook->location_.y == y) {
        assert(rook->location_.x != x);
        int minx = rook->location_.x < x ? rook->location_.x : x;
        int maxx = rook->location_.x > x ? rook->location_.x : x;
        for(x = minx+1; x<maxx; x++) {
            if(stone_map_[x][y]) return false;
        }
        return true;
    }
    else return false;
}
bool StoneMap::canCannonMove(Stone *cannon, int x, int y) {
    if(cannon->location_.x == x) {
        assert(cannon->location_.y != y);
        int miny = cannon->location_.y < y ? cannon->location_.y : y;
        int maxy = cannon->location_.y > y ? cannon->location_.y : y;
        
        if(stone_map_[x][y] != nullptr) {
            // 需要炮架子
            int cnt = 0;
            for(y = miny + 1; y<maxy; y++) {
                if(stone_map_[x][y]) cnt++; 
            }
            return cnt == 1;
        }
        else {
            for(y = miny+1; y<maxy; y++) {
                if(stone_map_[x][y]) return false;
            }
            return true;
        }
    }
    else if(cannon->location_.y == y) {
        assert(cannon->location_.x != x);
        int minx = cannon->location_.x < x ? cannon->location_.x : x;
        int maxx = cannon->location_.x > x ? cannon->location_.x : x;

        if(stone_map_[x][y] != nullptr) {
            // 需要炮架子
            int cnt = 0;
            for(x = minx + 1; x<maxx; x++) {
                if(stone_map_[x][y]) cnt++; 
            }
            return cnt == 1;
        }
        else {
            for(x = minx+1; x<maxx; x++) {
                if(stone_map_[x][y]) return false;
            }
            return true;
        }
    }
    else return false;
}
bool StoneMap::canPawnMove(Stone *pawn, int x, int y) {
    if((pawn->location_.x - x) * (pawn->location_.x - x) + 
        (pawn->location_.y - y) * (pawn->location_.y - y) != 1) return false;
    
    else if(pawn->up_or_down_ == Stone::UpOrDown::Up) {
        if(y < pawn->location_.y) return false;
        else return ! (pawn->location_.y <= 4 && pawn->location_.x != x) ;
    }
    else {
        if(y > pawn->location_.y) return false;
        else return ! (pawn->location_.y >= 5 && pawn->location_.x != x) ; 
    }
}

void StoneMap::regret() {
    if(steps_.empty()) return;
    Step step = steps_.top();
    steps_.pop();

    const int from_x = step.from_.x, from_y = step.from_.y;
    assert(! stone_map_[from_x][from_y]);
    step.mover_->location_.x = from_x;
    step.mover_->location_.y = from_y;

    stone_map_[from_x][from_y] = step.mover_;
    stone_map_[step.to_.x][step.to_.y] = step.killee_;

    if(step.killee_) {
        step.killee_->alive_ = true;
    }

    selected_stone_ = nullptr;
    from_.x = from_.y = to_.x = to_.y = -2;

    switchTurn();
}
