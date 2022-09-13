#include "stonemap.h"
#include "settings.h"
#include "asset.h"


void StoneMap::init()
{  
    memset(stones_, 0, sizeof(stones_));
    Settings &settings = Settings::getInstance();

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
        user = Stone::StoneColor::Red;
        computor = Stone::StoneColor::Black;
    }
    else {
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
}

void StoneMap::onBoardClicked(int x, int y) {
    if(selected_stone_ != nullptr) {
        int from_x = selected_stone_->location_.x;
        int from_y = selected_stone_->location_.y;
        stone_map_[from_x][from_y] = nullptr;
        stone_map_[x][y] = selected_stone_;
        selected_stone_->location_.x = x;
        selected_stone_->location_.y = y;
        selected_stone_ = nullptr;

        from_.x = from_x;
        from_.y = from_y;
        to_.x = x;
        to_.y = y;
    }
    else {
        selected_stone_ = stone_map_[x][y];
        from_.x = from_.y = to_.x = to_.y = -1;
    }
}

