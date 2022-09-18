#include "game.h"
#include "settings.h"
#include "computerplayer.h"

Game::Game() {
    selected_stone_ = nullptr;
    game_over_ = true;
    

    Settings &settings = Settings::getInstance();
    player_color_ = settings.choose_red_ ? StoneColor::Red : StoneColor::Black;
    stone_map_.init(! settings.choose_red_ ? Stone::UpOrDown::Up : Stone::UpOrDown::Down);
}

void Game::onBoardClicked(int x, int y) {
    assert(x >=0 && x < StoneMap::cols_ && y >= 0 && y < StoneMap::raws_);
    from_.x = from_.y = to_.x = to_.y = -2;

    if(stone_map_.getTurn() != Stone::UpOrDown::Down) return;
    
    else if(selected_stone_ == nullptr) {
        // 选择一个棋子
        if(stone_map_.getStoneOnMap(x, y) != nullptr && stone_map_.getStoneOnMap(x, y)->up_or_down_ == stone_map_.getTurn()) {
            // 选择了己方棋子
            selected_stone_ = stone_map_.getStoneOnMap(x, y);
        }
        from_.x = from_.y = to_.x = to_.y = -2;
    }
    else {
        assert(selected_stone_->up_or_down_ == stone_map_.getTurn() );
        if(stone_map_.getStoneOnMap(x, y) != nullptr && stone_map_.getStoneOnMap(x, y)->up_or_down_ == stone_map_.getTurn() ) {
            // 重新选择棋子
            selected_stone_ = stone_map_.getStoneOnMap(x, y);
            from_.x = from_.y = to_.x = to_.y = -2;
        }
        else {
            Step step(selected_stone_, x, y, stone_map_.getStoneOnMap(x, y));
            // 移动或吃子
            if(stone_map_.canMove(step)) {
                steps_.push(step);
                stone_map_.makeMove(step);

                from_.x = step.from_.x; from_.y = step.from_.y; to_.x = step.to_.x; to_.y = step.to_.y;
                
            }
            else {                    
                from_.x = from_.y = to_.x = to_.y = -2;
            }
            selected_stone_ = nullptr;
        }
    }

    // 最后再检查一下是否结束
    if(! stone_map_[StoneMap::StoneID::UpKing].alive_ || ! stone_map_[StoneMap::StoneID::DownKing].alive_) {
        game_over_ = true;
        player_win_ = ! stone_map_[StoneMap::StoneID::UpKing].alive_;
    }

    // 电脑走
    if(!game_over_ && stone_map_.getTurn() == Stone::UpOrDown::Up) {
        player_.setStoneMap(stone_map_);
        player_.playAsync();
    }
}



