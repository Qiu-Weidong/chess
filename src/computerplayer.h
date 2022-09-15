#ifndef CHESS_COMPUTORPLAYER_H_
#define CHESS_COMPUTORPLAYER_H_
#include "stonemap.h"
#include "step.h"
#include <vector>

class ComputerPlayer {

    StoneMap &map_;
    int max_depth_;

    int getMax(int current_depth) ;

    int getMin(int current_depth) ;
    
public:
    ComputerPlayer(StoneMap &map) : map_(map) { max_depth_ = 2; }
    Step play(); 

};
#endif // CHESS_COMPUTORPLAYER_H_
