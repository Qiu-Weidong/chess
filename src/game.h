#ifndef CHESS_GAME_H_
#define CHESS_GAME_H_
#include <map>
#include <array>
#include "stonemap.h"
#include "computerplayer.h"
#include "SFML/Graphics.hpp"


class Game
{
public:
    enum class StoneColor {
        Red, Black
    } ;
private:
    bool player_win_, game_over_;

    // map 游戏的主要逻辑
    StoneMap stone_map_;

    std::stack<Step> steps_;
    Stone *selected_stone_;
    StoneColor player_color_;

    ComputerPlayer player_;
public:
    Game();

    void onBoardClicked(int x, int y) ;

    struct { int x, y; } from_, to_;

    bool isGameOver() const { return game_over_; }

    bool isPlayerTurn() const {
        return stone_map_.getTurn() == Stone::UpOrDown::Down;
    }

    bool isComputerTurn() const { return ! isPlayerTurn(); }

    void checkComputerStep() {
        auto &future = player_.getStep();
        std::future_status status = future.wait_for(std::chrono::milliseconds(300));
        if(status != std::future_status::ready) return;

        Step step = player_.getStep().get();
        step.mover_ = stone_map_.getStoneOnMap(step.from_.x, step.from_.y);
        step.killee_ = stone_map_.getStoneOnMap(step.to_.x, step.to_.y);
        steps_.push(step);
        stone_map_.makeMove(step);
        from_.x = step.from_.x; from_.y = step.from_.y; to_.x = step.to_.x; to_.y = step.to_.y;

        if(! stone_map_[StoneMap::StoneID::UpKing].alive_ || ! stone_map_[StoneMap::StoneID::DownKing].alive_) {
        game_over_ = true;
        player_win_ = ! stone_map_[StoneMap::StoneID::UpKing].alive_;
    }
    }

    Stone *getSelectedStone() const { return selected_stone_; }

    const StoneMap::StoneArray &getAllStones() const { return stone_map_.getAllStones(); }

    StoneColor getPlayerColor() const {
        return player_color_;
    }

    bool isPlayerWin() const { 
        return game_over_ && player_win_; 
    }

    void start() {
        game_over_ = false;
        selected_stone_ = nullptr;
        from_.x = from_.y = to_.x = to_.y = -2;

        stone_map_.init( (player_color_ == Game::StoneColor::Red) ?
            Stone::UpOrDown::Down : Stone::UpOrDown::Up);
        while(! steps_.empty()) steps_.pop();
    }

    void regret() {
        if(steps_.empty()) return ;
        Step step = steps_.top();
        steps_.pop();

        stone_map_.revokeMove(step);
        from_.x = from_.y = to_.x = to_.y = -2;
        selected_stone_ = nullptr;
    }

};
#endif // CHESS_GAME_H_
