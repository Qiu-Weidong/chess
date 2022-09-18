#ifndef CHESS_STEP_H_
#define CHESS_STEP_H_
#include <cassert>
#include "stone.h"


struct Step {
    struct { int x, y; } from_;
    struct { int x, y; } to_;
    Stone *mover_;
    Stone *killee_;

    Step() = default;

    Step(Stone *mover, int from_x, int from_y, int to_x, int to_y, Stone *killee=nullptr) {
        mover_ = mover; killee_ = killee;
        from_.x = from_x; from_.y = from_y;
        to_.x = to_x; to_.y = to_y;
    }

    Step(Stone *mover, int dest_x, int dest_y, Stone *killee=nullptr) {
        assert(mover);
        mover_ = mover;
        from_.x = mover->location_.x;
        from_.y = mover->location_.y;
        to_.x = dest_x;
        to_.y = dest_y;
        killee_ = killee;
    }
};
#endif // CHESS_STEP_H_

