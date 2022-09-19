#include "computerplayer.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>


Step ComputerPlayer::play() {
    auto t1 = clock();
    
    memset(history_table_, 0, sizeof(history_table_));

    std::vector<Step> best_steps;
    std::vector<Step> possible_steps = map_.generatePossibleSteps();
    int alpha = -inf - max_depth_ - 1, beta = inf + max_depth_ + 1;

    for(const auto &step : possible_steps) {
        map_.makeMove(step);
        int value = getMin(max_depth_ - 1, alpha-1, beta); // 位于区间(alpha, beta)的值为真实值
        map_.revokeMove(step);

        if(value > alpha) {
            assert(alpha < beta);
            alpha = value;
            best_steps.clear();
            best_steps.push_back(step);
        } else if(value == alpha) {
            best_steps.push_back(step);
        }
    }

    int index = rand() % best_steps.size();
    
    auto t2 = clock();
    std::cout << t2 - t1  << std::endl;
    return best_steps[index];
}

// 获取最小值，但不能小于alpha
int ComputerPlayer::getMin(int current_depth, int alpha, int beta) {
    if(current_depth <= 0) return map_.evaluate();
    else if(! map_[(int)StoneMap::StoneID::UpKing].alive_) return -inf - current_depth;
    else if(! map_[(int)StoneMap::StoneID::DownKing].alive_) return inf + current_depth;

    std::vector<Step> possible_steps = map_.generatePossibleSteps();
    for(Step &step : possible_steps) step.weight_ = getHistoryScore(step);
    std::sort(possible_steps.begin(), possible_steps.end(), [](const Step &step1, const Step & step2) {
        return step1.weight_ > step2.weight_;
    });

    for(const auto &step : possible_steps) {
        map_.makeMove(step);
        int value = getMax(current_depth - 1, alpha, beta);
        map_.revokeMove(step);

        if(value < beta) {
            beta = value;
            if(alpha >= beta) {
                addHistoryScore(step, current_depth);
                return alpha;
            }
        }
    }
    return beta;
}
// 获取最大值，但不能超过beta
int ComputerPlayer::getMax(int current_depth, int alpha, int beta) {
    if(current_depth <= 0) return map_.evaluate();
    else if(! map_[(int)StoneMap::StoneID::UpKing].alive_) return -inf - current_depth;
    else if(! map_[(int)StoneMap::StoneID::DownKing].alive_) return inf + current_depth;

    std::vector<Step> possible_steps = map_.generatePossibleSteps();
    for(Step &step : possible_steps) step.weight_ = getHistoryScore(step);
    std::sort(possible_steps.begin(), possible_steps.end(), [](const Step &step1, const Step & step2) {
        return step1.weight_ > step2.weight_;
    });

    for(const auto &step : possible_steps) {
        map_.makeMove(step);
        int value = getMin(current_depth - 1, alpha, beta);
        map_.revokeMove(step);
        if(value > alpha)  {
            alpha = value;
            if(alpha >= beta) { 
                addHistoryScore(step, current_depth);
                return beta; 
            }
        }
    }
    return alpha;
}



/*
搜索深度 5 ~ 6
995 763 552 329 328 265 427 648 203 924 1006 1189 1079 1278 1085 947 618 497 1421 1034 2389
1153 680 139 121 223 197 155 79 347 346 255 394 264 323 344 240 222 134 207 183 192 115 165
157 228 201 77 83 82 41 47 110 906 1798 1048 619 2306 3551 2585 7643 1542 510

615 2749 224 199 429 569 663 347 950 677 527 926 727 1107 5318 7912 10939 2241 6448 2244 6490 4338

加入历史启发(每当触发剪枝，即可加入启发表)
305 152 447 281 166 550 410 485 312 663 415 373 620 464
621 363 408 463 288 442 234 130 2389 2648 2161 3681 3485 654 731 1710 1371 1075 798 607 646

2342 2206 1223 1044 1060 1087 1686 1830 1448 1674 2364 1568 2612 3465 4584 5560 3768 4172 1904 3281
10489 10245 35283 23724 7604 4777 4828 4159 4203 937 618 513 380 243 359 1083 776 1302 6149 2871
*/


