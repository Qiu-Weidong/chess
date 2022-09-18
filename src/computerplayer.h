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

    std::future<Step> step_;

    int getMax(int current_depth, int alpha, int beta) ;

    int getMin(int current_depth, int alpha, int beta) ;
    
public:
    void setStoneMap(const StoneMap &map) { 
        map_ = map; 

        int cnt = 0;
        for(int i=0; i<StoneMap::stone_cnt_; i++) {
            if(map_[i].alive_) cnt++;
        }

        max_depth_ = (82 - cnt) / 10; 
    }
    void playAsync() {
        auto func = std::bind(&ComputerPlayer::play, this);
        step_ = std::async(std::launch::async, func);
    }
    Step play(); 

    std::future<Step> &getStep() { return step_; } ;
};
#endif // CHESS_COMPUTORPLAYER_H_
