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
    void setStoneMap(const StoneMap &map) { map_ = map; max_depth_ = 5; }
    void playAsync() {
        auto func = std::bind(&ComputerPlayer::play, this);
        step_ = std::async(std::launch::async, func);
    }
    Step play(); 

    std::future<Step> &getStep() { return step_; } ;
};
#endif // CHESS_COMPUTORPLAYER_H_
