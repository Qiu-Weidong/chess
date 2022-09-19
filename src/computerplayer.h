#ifndef CHESS_COMPUTORPLAYER_H_
#define CHESS_COMPUTORPLAYER_H_
#include "stonemap.h"
#include "step.h"
#include <future>
#include <functional>


class ComputerPlayer {
    static const int inf = 0x3f3f3f3f;
    StoneMap map_;
    int max_depth_;
    static const int n_thread_ = 3;

    std::future<Step> step_;

    int getMax(int current_depth, int alpha, int beta) ;

    int getMin(int current_depth, int alpha, int beta) ;
    
    int history_table_[90][90];

    inline int getHistoryScore(const Step &step) {
        int n_from = step.from_.y * 9 + step.from_.x;
        int n_dest = step.to_.y * 9 + step.to_.y;
        return history_table_[n_from][n_dest];
    }

    inline void addHistoryScore(const Step &step, int depth) {
        int n_from = step.from_.y * 9 + step.from_.x;
        int n_dest = step.to_.y * 9 + step.to_.y;
        history_table_[n_from][n_dest] += (1 << depth);
    }

public:
    void setStoneMap(const StoneMap &map) { 
        map_ = map; 

        int cnt = 0;
        for(int i=0; i<StoneMap::stone_cnt_; i++) {
            if(map_[i].alive_) cnt++;
        }

        max_depth_ = (92 - cnt) / 10; 
    }

    void playAsync() {
        auto func = std::bind(&ComputerPlayer::play, this);
        step_ = std::async(std::launch::async, func);
    }

    Step play(); 

    std::future<Step> &getStep() { return step_; } 
};
#endif // CHESS_COMPUTORPLAYER_H_
