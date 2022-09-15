#include "computerplayer.h"
#include <iostream>


Step ComputerPlayer::play() {

    std::vector<Step> best_steps;
    std::vector<Step> possible_steps = map_.generatePossibleSteps();

    int alpha = 0x80000000, beta = 0x7fffffff;

    for(const auto &step : possible_steps) {
        map_.makeMove(step);
        int value = getMin(max_depth_ - 1, alpha, beta);
        map_.revokeMove(step);

        if(value > alpha) {
            assert(alpha < beta);
            alpha = value;
            best_steps.clear();
            best_steps.push_back(step);
        } //else if(value == alpha) {
        //     best_steps.push_back(step);
        // }
    }

    if(best_steps.size() > 1) {
        int index = rand() % best_steps.size();
        return best_steps[index];
    }
    return best_steps[0];

}
// 获取最小值，但不能小于alpha
int ComputerPlayer::getMin(int current_depth, int alpha, int beta) {
    if(current_depth <= 0) return map_.evaluate();

    std::vector<Step> possible_steps = map_.generatePossibleSteps();

    for(const auto &step : possible_steps) {
        map_.makeMove(step);
        int value = getMax(current_depth - 1, alpha, beta);
        map_.revokeMove(step);

        if(value < beta) {
            beta = value;
            if(alpha >= beta)
                return alpha;
        }
    }
    return beta;
}
// 获取最大值，但不能超过beta
int ComputerPlayer::getMax(int current_depth, int alpha, int beta) {
    if(current_depth <= 0) return map_.evaluate();

    std::vector<Step> possible_steps = map_.generatePossibleSteps();

    for(const auto &step : possible_steps) {
        map_.makeMove(step);
        int value = getMin(current_depth - 1, alpha, beta);
        map_.revokeMove(step);
        if(value > alpha)  {
            alpha = value;
            if(alpha >= beta) return beta;
        }
    }
    return alpha;
}




