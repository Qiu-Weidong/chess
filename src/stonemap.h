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

    int padding_left_;
    int padding_right_;
    int padding_top_;
    int padding_bottom_;
    int stone_radius_;

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
        for(int i=0; i<stone_cnt_; i++) {
            if(stone_map.stones_[i].alive_)
            {target.draw(stone_map.stones_[i].background_);
            target.draw(stone_map.stones_[i].text_);}
        }
        return target;
    }

    int getPaddingLeft() const {
        return padding_left_;
    }

    int getPaddingRight() const {
        return padding_right_;
    }

    int getPaddingTop() const {
        return padding_top_;
    }

    int getPaddingBottom() const {
        return padding_bottom_;
    }

    int getStoneRadius() const {
        return stone_radius_;
    }

    void setPadding(int left, int top) {
        padding_left_ = padding_right_ = left;
        padding_bottom_ = padding_top_ = top;
    }

    void setPadding(int left, int top, int right, int bottom) {
        padding_left_ = left; 
        padding_right_ = right; 
        padding_top_ = top; 
        padding_bottom_ = bottom;
    }

    void setStoneRadius(int stone_radius) {
        stone_radius_ = stone_radius;
    }

    sf::Sprite &getBoardSprite() {
        return board_;
    }

    sf::Sprite &getBoardBackgroundSprite() {
        return board_background_;
    }
};

#endif // CHESS_STONEMAP_H_
