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

std::vector<Step> StoneMap::generatePossibleSteps()  {
    std::vector<Step> possible_steps;

    int st = Stone::UpOrDown::Up == turn_ ? 0 : 16;
    int ed = Stone::UpOrDown::Up == turn_ ? 16 : 32;

    for(int i=st; i<ed; i++) {
        if(stones_[i].alive_)
            generatePossibleStoneSteps(stones_[i], possible_steps);
    }

    return std::move(possible_steps);
}

int StoneMap::evaluate() const {
    // todo 1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536 131072 
    // king 65536 rook 512 knight 320 pawn 128 cannon 320 bishop 256 mandarin 248
    int stone_values[] = { 65536, 248, 256, 320, 512, 320, 128 };
    int upscore = 0, downscore = 0;

    // 子力评估
    for(const auto &stone : stones_) {
        if(! stone.alive_ ) continue;
        stone.up_or_down_ == Stone::UpOrDown::Up ? upscore += stone_values[(int)stone.stone_type_] :
            downscore += stone_values[(int)stone.stone_type_];
    }

    
    return upscore - downscore ;
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
    if(step.to_.x < 3 || step.to_.x > 5 || 
        step.mover_->up_or_down_ == Stone::UpOrDown::Up && step.to_.y > 2 ||
        step.mover_->up_or_down_ == Stone::UpOrDown::Down && step.to_.y < 7) return false;
    
    else return ((step.from_.x - step.to_.x) * (step.from_.x - step.to_.x) + 
        (step.from_.y - step.to_.y) * (step.from_.y - step.to_.y) == 1) ;
}
bool StoneMap::canMandarinMove(const Step &step) {
    if(step.to_.x < 3 || step.to_.x > 5 || 
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


void StoneMap::generatePossibleKingSteps(Stone &king, std::vector<Step> &steps)  {
    generatePossibleKingOrPawnSteps(king, steps);
}
void StoneMap::generatePossibleMandarinSteps(Stone &mandarin, std::vector<Step> &steps)  {
    
    std::vector<Step> step_list ;
    if(mandarin.up_or_down_ == Stone::UpOrDown::Up) {
        step_list = {
            Step(&mandarin, 3, 0, stone_map_[3][0]), Step(&mandarin, 5, 0, stone_map_[5][0]),
            Step(&mandarin, 4, 1, stone_map_[4][1]), Step(&mandarin, 3, 2, stone_map_[3][2]),
            Step(&mandarin, 5, 2, stone_map_[5][2]),
        };
    } 
    else {
        step_list = {
            Step(&mandarin, 3, 7, stone_map_[3][7]), Step(&mandarin, 5, 7, stone_map_[5][7]),
            Step(&mandarin, 4, 8, stone_map_[4][8]), Step(&mandarin, 3, 9, stone_map_[3][9]),
            Step(&mandarin, 5, 9, stone_map_[5][9]),
        };
    }
    
    for(const Step & step : step_list) {
        if(canMove(step)) steps.push_back(step);
    }
}
void StoneMap::generatePossibleBishopSteps(Stone &bishop, std::vector<Step> &steps)  {
    std::vector<Step> step_list;

    if(bishop.up_or_down_ == Stone::UpOrDown::Up) {
        step_list = {Step(&bishop, 2, 0, stone_map_[2][0]), Step(&bishop, 6, 0, stone_map_[6][0]),
        Step(&bishop, 0, 2, stone_map_[0][2]), Step(&bishop, 4, 2, stone_map_[4][2]), 
        Step(&bishop, 8, 2, stone_map_[8][2]), Step(&bishop, 0, 4, stone_map_[0][4]),
        Step(&bishop, 6, 4, stone_map_[6][4]),};
    }
    else {
        step_list = {
            Step(&bishop, 2, 5, stone_map_[2][5]), Step(&bishop, 6, 5, stone_map_[6][5]),
            Step(&bishop, 0, 7, stone_map_[0][7]), Step(&bishop, 4, 7, stone_map_[4][7]),
            Step(&bishop, 8, 7, stone_map_[8][7]), Step(&bishop, 2, 9, stone_map_[2][9]),
            Step(&bishop, 6, 9, stone_map_[6][9]),
        };
    }
    
    for(const Step & step : step_list) {
        if(canMove(step)) steps.push_back(step);
    }

}
void StoneMap::generatePossibleKnightSteps(Stone &knight, std::vector<Step> &steps)  {
    const int dx[] = { 1, 1, -1, -1, 2, 2, -2, -2 };
    const int dy[] = { 2,-2,  2, -2, 1, -1, 1, -1 };

    for(int i=0; i<8; i++) {
        int x = knight.location_.x + dx[i];
        int y = knight.location_.y + dy[i];
        Step step(&knight, x, y, stone_map_[x][y]);
        if(canMove(step)) steps.push_back(step);
    }
}
void StoneMap::generatePossibleRookSteps(Stone &rook, std::vector<Step> &steps)  {
    generatePossibleRookOrCannonSteps(rook, steps);
}
void StoneMap::generatePossibleCannonSteps(Stone &cannon, std::vector<Step> &steps)  {
    generatePossibleRookOrCannonSteps(cannon, steps);
}
void StoneMap::generatePossiblePawnSteps(Stone &pawn, std::vector<Step> &steps)  {
    generatePossibleKingOrPawnSteps(pawn, steps);
}
void StoneMap::generatePossibleRookOrCannonSteps(Stone &stone, std::vector<Step> &steps) {
    // 横向
    for(int x=0, y=stone.location_.y; x<cols_; x++) {
        Step step(&stone, x, y, stone_map_[x][y]);
        if(canMove(step)) steps.push_back(step);
    }
    // 纵向
    for(int y=0, x=stone.location_.x; y < raws_; y++) {
        Step step(&stone, x, y, stone_map_[x][y]);
        if(canMove(step)) steps.push_back(step);
    }
}
void StoneMap::generatePossibleKingOrPawnSteps(Stone &stone, std::vector<Step> &steps) {
    const int dx[] = {  1, -1,  0,  0,  };
    const int dy[] = {  0,  0,  1, -1,  };

    for(int i=0; i<4; i++) {
        int x = stone.location_.x + dx[i];
        int y = stone.location_.y + dy[i];

        Step step(&stone, x, y, stone_map_[x][y]);
        if(canMove(step)) steps.push_back(step);
    }
}
void StoneMap::generatePossibleStoneSteps(Stone &stone, std::vector<Step> &steps) {
    switch(stone.stone_type_) {
        case Stone::StoneType::King:
        case Stone::StoneType::Pawn:
            generatePossibleKingOrPawnSteps(stone, steps);
            break;
        case Stone::StoneType::Rook:
        case Stone::StoneType::Cannon:
            generatePossibleRookOrCannonSteps(stone, steps);
            break;
        case Stone::StoneType::Mandarin:
            generatePossibleMandarinSteps(stone, steps);
            break;
        case Stone::StoneType::Bishop:
            generatePossibleBishopSteps(stone, steps);
            break;
        case Stone::StoneType::Knight:
            generatePossibleKnightSteps(stone, steps);
            break;
        default:
            break;
    }
}