#include "stonemap.h"
#include "asset.h"


void StoneMap::init(Stone::UpOrDown turn)
{  
    for(int i=0; i<cols_; i++) {
        for(int j=0; j<raws_; j++) stone_map_[i][j] = nullptr;
    }

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

    for(int i=0; i<stone_cnt_; i++) {
        stones_[i].up_or_down_ = i < (int)Stone::StoneID::DownPawnLeft ? Stone::UpOrDown::Up : Stone::UpOrDown::Down;
        stones_[i].alive_ = true;
        
        int x = locationx[i], y = locationy[i];
        stones_[i].location_.x = x;
        stones_[i].location_.y = y;
        stones_[i].stone_type_ = types[i];
        stone_map_[x][y] = &stones_[i];
    }

    turn_ = turn;

}

bool StoneMap::canMove(const Step &step) {
    if(! step.mover_ || step.to_.x < 0 || step.to_.x > 8 || step.to_.y < 0 || step.to_.y > 9 || 
        step.from_.x < 0 || step.from_.x > 8 || step.from_.y < 0 || step.from_.y > 9 ||
        step.killee_ != nullptr && step.killee_->up_or_down_ == step.mover_->up_or_down_ ||
        step.from_.x == step.to_.x && step.from_.y == step.to_.y) return false;

    bool ret = true;
    switch(step.mover_->stone_type_) {
        case Stone::StoneType::King:
            ret = canKingMove(step);
            break;
        case Stone::StoneType::Mandarin:
            ret = canMandarinMove(step);
            break;
        case Stone::StoneType::Bishop:
            ret = canBishopMove(step);
            break;
        case Stone::StoneType::Knight:
            ret = canKnightMove(step);
            break;
        case Stone::StoneType::Rook:
            ret = canRookMove(step);
            break;
        case Stone::StoneType::Cannon:
            ret = canCannonMove(step);
            break;
        case Stone::StoneType::Pawn:
            ret = canPawnMove(step);
            break;
        default:
            ret = false;
            break;
    }
    
    if(! ret) return ret;
    
    // 先尝试移动，然后复位
    makeMove(step);

    // 检查将帅碰面
    ret = ! isKingMeeted();

    revokeMove(step);

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

bool StoneMap::canKingMove(const Step &step) {
    if(step.to_.x < 3 || step.to_.y > 5 || 
        step.mover_->up_or_down_ == Stone::UpOrDown::Up && step.to_.y > 2 ||
        step.mover_->up_or_down_ == Stone::UpOrDown::Down && step.to_.y < 7) return false;
    
    else return ((step.from_.x - step.to_.x) * (step.from_.x - step.to_.x) + 
        (step.from_.y - step.to_.y) * (step.from_.y - step.to_.y) == 1) ;
}
bool StoneMap::canMandarinMove(const Step &step) {
    if(step.to_.x < 3 || step.to_.y > 5 || 
        step.mover_->up_or_down_ == Stone::UpOrDown::Up && step.to_.y > 2 ||
        step.mover_->up_or_down_ == Stone::UpOrDown::Down && step.to_.y < 7) return false;
    else return ((step.from_.x - step.to_.x) * (step.from_.x - step.to_.x) + 
        (step.from_.y - step.to_.y) * (step.from_.y - step.to_.y) == 2) ;
}
bool StoneMap::canBishopMove(const Step &step) {
    if(step.mover_->up_or_down_ == Stone::UpOrDown::Up && step.to_.y > 4 ||
        step.mover_->up_or_down_ == Stone::UpOrDown::Down && step.to_.y < 5 || 
        (step.from_.x - step.to_.x) * (step.from_.x - step.to_.x) + 
        (step.from_.y - step.to_.y) * (step.from_.y - step.to_.y) != 8) 
        return false;
    int cx = (step.from_.x + step.to_.x) / 2;
    int cy = (step.from_.y + step.to_.y) / 2;
    return ! stone_map_[cx][cy] ;
}
bool StoneMap::canKnightMove(const Step &step) {
    if ((step.from_.x - step.to_.x) * (step.from_.x - step.to_.x) + 
        (step.from_.y - step.to_.y) * (step.from_.y - step.to_.y) != 5) 
        return false;
    else if((step.from_.x - step.to_.x) * (step.from_.x - step.to_.x) == 1) {
        int cx = step.from_.x;
        int cy = (step.from_.y + step.to_.y) / 2;
        return ! stone_map_[cx][cy]; 
    }
    else {
        int cx = (step.from_.x + step.to_.x) / 2;
        int cy = step.from_.y;
        return ! stone_map_[cx][cy]; 
    }
}
bool StoneMap::canRookMove(const Step &step) {
    if(step.from_.x == step.to_.x) {
        assert(step.from_.y != step.to_.y);
        int miny = step.from_.y < step.to_.y ? step.from_.y : step.to_.y;
        int maxy = step.from_.y > step.to_.y ? step.from_.y : step.to_.y;
        for(int x=step.from_.x, y=miny+1; y < maxy; y++) {
            if(stone_map_[x][y]) return false;
        }
        return true;
    }
    else if(step.from_.y == step.to_.y) {
        assert(step.from_.x != step.to_.x);
        int minx = step.from_.x < step.to_.x ? step.from_.x : step.to_.x;
        int maxx = step.from_.x > step.to_.x ? step.from_.x : step.to_.x;
        for(int x=minx+1, y=step.from_.y; x < maxx; x++) {
            if(stone_map_[x][y]) return false;
        }
        return true;
    }
    else return false;
}
bool StoneMap::canCannonMove(const Step &step) {
    if(step.from_.x == step.to_.x) {
        assert(step.from_.y != step.to_.y);
        int miny = step.from_.y < step.to_.y ? step.from_.y : step.to_.y;
        int maxy = step.from_.y > step.to_.y ? step.from_.y : step.to_.y;
        
        if(step.killee_ != nullptr) {
            // 需要炮架子
            int cnt = 0;
            for(int y = miny + 1, x=step.from_.x; y<maxy; y++) {
                if(stone_map_[x][y]) cnt++; 
            }
            return cnt == 1;
        }
        else {
            for(int y = miny+1, x=step.from_.x; y<maxy; y++) {
                if(stone_map_[x][y]) return false;
            }
            return true;
        }
    }
    else if(step.from_.y == step.to_.y) {
        assert(step.from_.x != step.to_.x);
        int minx = step.from_.x < step.to_.x ? step.from_.x : step.to_.x;
        int maxx = step.from_.x > step.to_.x ? step.from_.x : step.to_.x;

        if(step.killee_ != nullptr) {
            // 需要炮架子
            int cnt = 0;
            for(int x = minx + 1, y=step.from_.y; x<maxx; x++) {
                if(stone_map_[x][y]) cnt++; 
            }
            return cnt == 1;
        }
        else {
            for(int x = minx+1, y=step.from_.y; x<maxx; x++) {
                if(stone_map_[x][y]) return false;
            }
            return true;
        }
    }
    else return false;
}
bool StoneMap::canPawnMove(const Step &step) {
    if((step.from_.x - step.to_.x) * (step.from_.x - step.to_.x) + 
        (step.from_.y - step.to_.y) * (step.from_.y - step.to_.y) != 1) return false;
    
    else if(step.mover_->up_or_down_ == Stone::UpOrDown::Up) {
        if(step.to_.y < step.from_.y) return false;
        else return ! (step.from_.y <= 4 && step.from_.x != step.to_.x) ;
    }
    else {
        if(step.to_.y > step.from_.y) return false;
        else return ! (step.from_.y >= 5 && step.from_.x != step.to_.x) ; 
    }
}


void StoneMap::makeMove(const Step &step) {
    assert(step.mover_);
    assert(stone_map_[step.from_.x][step.from_.y] == step.mover_);
    assert(stone_map_[step.to_.x][step.to_.y] == step.killee_);

    if(step.killee_)
        step.killee_->alive_ = false;
    stone_map_[step.from_.x][step.from_.y] = nullptr;
    stone_map_[step.to_.x][step.to_.y] = step.mover_;
    step.mover_->location_.x = step.to_.x;
    step.mover_->location_.y = step.to_.y;

    switchTurn();
}

void StoneMap::revokeMove(const Step &step) {
    assert(! stone_map_[step.from_.x][step.from_.y]);

    step.mover_->location_.x = step.from_.x;
    step.mover_->location_.y = step.from_.y;

    stone_map_[step.from_.x][step.from_.y] = step.mover_;
    stone_map_[step.to_.x][step.to_.y] = step.killee_;

    if(step.killee_) step.killee_->alive_ = true;

    switchTurn();
}
