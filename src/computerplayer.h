#ifndef CHESS_COMPUTORPLAYER_H_
#define CHESS_COMPUTORPLAYER_H_
#include "stonemap.h"
#include "step.h"
#include "evaluator.h"
#include "stepgenerator.h"
#include <vector>

class ComputerPlayer {

    Stone * map_[StoneMap::cols_][StoneMap::raws_];
    std::array<Stone, StoneMap::stone_cnt_> stones_;

    int max_depth_;
    
    void fakeMove(const Step &step) {
        assert(step.mover_);
        assert(map_[step.to_.x][step.to_.y] == step.killee_);

        if(step.killee_) {
            step.killee_->alive_ = false;
        }

        map_[step.from_.x][step.from_.y] = nullptr;
        map_[step.to_.x][step.to_.y] = step.mover_;

        step.mover_->location_.x = step.to_.x;
        step.mover_->location_.y = step.to_.y;
    }

    void unMove(const Step &step) {
        assert(! map_[step.from_.x][step.from_.y]);
        step.mover_->location_.x = step.from_.x;
        step.mover_->location_.y = step.from_.y;

        map_[step.from_.x][step.from_.y] = step.mover_;
        map_[step.to_.x][step.to_.y] = step.killee_;

        if(step.killee_) {
            step.killee_->alive_ = true;
        }
    }

    int getMax(int current_depth) {
        if(current_depth <= 0) {
            return Evaluator::evaluate(map_, stones_, Stone::UpOrDown::Up); // return evaluator();
        }

        // 生成所有可能的移动
        std::vector<Step> possible_steps = StepGenerator::generatePossibleSteps(map_, stones_, Stone::UpOrDown::Up);

        int bestvalue = 0x80000000; // 初始化为极小值
        for(const auto &step : possible_steps) {
            fakeMove(step);
            int value = getMin(current_depth - 1);
            unMove(step);
            if(value > bestvalue) { 
                bestvalue = value;
            }
        }

        return bestvalue;
    }

    int getMin(int current_depth) {
        if(current_depth <= 0) return Evaluator::evaluate(map_, stones_, Stone::UpOrDown::Down);

        std::vector<Step> possible_steps = StepGenerator::generatePossibleSteps(map_, stones_, Stone::UpOrDown::Down);
        int bestvalue = 0x7fffffff;
        for(const auto &step : possible_steps) {
            fakeMove(step);
            int value = getMax(current_depth - 1);
            unMove(step);
            if(value < bestvalue) bestvalue = value;
        }
        return bestvalue;
    }
    
public:
    Step play(const StoneMap::StoneArray &stones) {
        // 准备map和stones
        stones_ = stones;
        memset(map_, 0, sizeof(map_));
        for(auto &stone : stones_) {
            int x = stone.location_.x;
            int y = stone.location_.y;

            assert(0 <= x && x < 9 && 0 <= y && y < 10);
            map_[x][y] = &stone;
        }
        // 根据剩余的棋子数量来决定搜索深度

        std::vector<Step> steps;
        std::vector<Step> possible_steps = StepGenerator::generatePossibleSteps(map_, stones_, Stone::UpOrDown::Up);
        int bestvalue = 0x80000000;
        for(const auto &step : possible_steps) {
            fakeMove(step);
            int value = getMin(max_depth_ - 1);
            unMove(step);
            
            if(value > bestvalue) {
                bestvalue = value;
                steps.clear();
                steps.push_back(step);
            }
            else if(value == bestvalue) {
                steps.push_back(step);
            }
        }

        // 从 steps 里面随便返回一个
        if(steps.size() > 1) {
            int index = rand() % steps.size();
            return steps[index];
        }
        return steps[0];
    }
};
#endif // CHESS_COMPUTORPLAYER_H_
