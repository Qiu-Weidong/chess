#ifndef CHESS_STONEMAP_H_
#define CHESS_STONEMAP_H_
#include <array>
#include "stone.h"
#include "rapidjson/document.h"



class StoneMap {
    
public:
    static const int stone_cnt_ = 32;
    static const int raws = 10;
    static const int cols = 9;

private:
    Stone *stone_map_[cols][raws];
    Stone stones_[stone_cnt_];

    sf::Sprite board_, board_background_;

public:
    void init(); // 初始化为开始局面
    Stone &operator[](int x) {
        assert(x >=0 && x < stone_cnt_);
        return stones_[x];
    }

    Stone &get(int x) {
        assert(x >=0 && x < stone_cnt_);
        return stones_[x];
    }

    friend sf::RenderTarget &operator<<(sf::RenderTarget &target, const StoneMap &stone_map) {
        target.draw(stone_map.board_background_);
        target.draw(stone_map.board_);
        for(int i=0; i<stone_cnt_; i++) {
            if(stone_map.stones_[i].alive_)
            {target.draw(stone_map.stones_[i].background_);
            target.draw(stone_map.stones_[i].text_);}
        }
        return target;
    }

    sf::Sprite &getBoardSprite() {
        return board_;
    }

    sf::Sprite &getBoardBackgroundSprite() {
        return board_background_;
    }
};

#endif // CHESS_STONEMAP_H_
