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
        
        stones_[i].location_.x = locationx[i];
        stones_[i].location_.y = locationy[i];
        stones_[i].stone_type_ = types[i];

        stones_[i].color_ = i < (int)Stone::StoneID::DownPawnLeft ? computor : user;
    }
}

