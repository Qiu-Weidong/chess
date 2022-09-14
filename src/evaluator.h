#ifndef CHESS_EVALUATOR_H_
#define CHESS_EVALUATOR_H_
#include "stone.h"
#include "stonemap.h"

// 用于对局面进行评估的类
class Evaluator {
private:
    
public:
    static int evaluate(const Stone *map[StoneMap::cols_][StoneMap::raws_], const StoneMap::StoneArray &stones, Stone::UpOrDown turn);
};
#endif // CHESS_EVALUATOR_H_

