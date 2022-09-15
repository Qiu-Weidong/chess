#include "computerplayer.h"
#include <iostream>


Step ComputerPlayer::play() {

    std::vector<Step> best_steps;
    std::vector<Step> possible_steps = map_.generatePossibleSteps();

    int bestvalue = 0x80000000;

    for(const auto &step : possible_steps) {
        map_.makeMove(step);
        int value = getMin(max_depth_ - 1);

        map_.revokeMove(step);

        if(value > bestvalue) {
            bestvalue = value;
            best_steps.clear();
            best_steps.push_back(step);
        }
        else if(value == bestvalue) {
            best_steps.push_back(step);
        }
    }

    if(best_steps.size() > 1) {
        int index = rand() % best_steps.size();
        return best_steps[index];
    }
    return best_steps[0];

}

int ComputerPlayer::getMin(int current_depth) {
    if(current_depth <= 0) return map_.evaluate();

    std::vector<Step> possible_steps = map_.generatePossibleSteps();
    int bestvalue = 0x7fffffff;

    for(const auto &step : possible_steps) {
        map_.makeMove(step);
        int value = getMax(current_depth - 1);
        map_.revokeMove(step);

        if(value < bestvalue) bestvalue = value;
    }
    return bestvalue;
}

int ComputerPlayer::getMax(int current_depth) {
    if(current_depth <= 0) return map_.evaluate();

    std::vector<Step> possible_steps = map_.generatePossibleSteps();

    int bestvalue = 0x80000000;

    for(const auto &step : possible_steps) {
        map_.makeMove(step);
        int value = getMin(current_depth - 1);
        map_.revokeMove(step);
        if(value > bestvalue) bestvalue = value;
    }
    return bestvalue;
}




