#ifndef CHESS_STEPGENERATOR_H_
#define CHESS_STEPGENERATOR_H_
#include <vector>
#include "step.h"
#include "stone.h"
#include "stonemap.h"


class StepGenerator {
public:
    static std::vector<Step> generatePossibleSteps(Stone *map[StoneMap::cols_][StoneMap::raws_],
        const StoneMap::StoneArray &stones, Stone::UpOrDown turn );
};
#endif // CHESS_STEPGENERATOR_H_
