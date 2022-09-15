#ifndef CHESS_COMPUTORPLAYER_H_
#define CHESS_COMPUTORPLAYER_H_
#include "stonemap.h"
#include "step.h"
#include <vector>

class ComputerPlayer {
    static const int inf = 0x3f3f3f3f;
    StoneMap &map_;
    int max_depth_;

    int getMax(int current_depth, int alpha, int beta) ;

    int getMin(int current_depth, int alpha, int beta) ;
    
public:
    ComputerPlayer(StoneMap &map) : map_(map) { max_depth_ = 5; }
    Step play(); 

};
#endif // CHESS_COMPUTORPLAYER_H_
