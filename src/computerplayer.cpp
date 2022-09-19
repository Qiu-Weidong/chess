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

2220 1482 840 1841 1459 542 1258 1115 2072 1491 2476 1688 1568 778 1200 591 784 781 373 276 436

2858 1748 1534 1720 1232 600 541 1436 1011 519 288 1065

2265 1477 874 1897 1612 555 996 821 2318 2371 640 666 2613 3293 3082 3373 3154 3586 2708 4046 2452 1682 581 880 2636 974 1039


3455 2045 1667 1220 3118 1688 428 129 334 368 708 924 1008 1452 2480 1112
640 396 951 674 832 476 670 1448 651 214
795 942 568 522 360 627 7797 10750
2039 4404 1097 5484 4799 2047 417 910 343 135 39 71 254 155 44 122
22 125 197 92 116 57 215 162 210 269 158 146
335 85 85 71 108 83 82 83 55 84 92 84
57 84 88 3267 1853 1633 2229 1282 1801 2250 1986 1161 647 324 1217 779 1169 1794 2680 2513
6737 7739 8094 4019 3888 5925 4168 2025
5602 4422 5019 5188 6664 4626 5969 5050 3350 7087 4942 4164 2267 4209 2587
2361 1524 2778 2862 2088 3497 1691 879 1542 1635 7065 853 4761 3259
1742 2428 3216 2293 3029 3508 6144 8047 11328 9386 4865 3491 6102
4590 1469 3866 2955 5573 2028 1341 7265 3374 3664 5726 3844 3502
*/


