#include "settings.h"
#include "rapidjson/istreamwrapper.h"
#include "rapidjson/Document.h"

Settings *Settings::p_settings_ = nullptr;
void Settings::loadFromFile(std::ifstream &in)
{
    using value = rapidjson::Value;

    rapidjson::IStreamWrapper isw(in);
    rapidjson::Document document;
    document.ParseStream(isw);

    
    { // 解析padding
        auto it = document.FindMember("padding");
        if (it != document.MemberEnd() && it->value.IsObject())
        {
            value &v_padding = it->value;
            auto it1 = v_padding.FindMember("left");
            if (it1 != v_padding.MemberEnd() && it1->value.IsInt())
                padding_.left_ = padding_.right_ = it1->value.GetInt();
            auto it2 = v_padding.FindMember("right");
            if (it2 != v_padding.MemberEnd() && it2->value.IsInt())
                padding_.right_ = it2->value.GetInt();
            auto it3 = v_padding.FindMember("top");
            if (it3 != v_padding.MemberEnd() && it3->value.IsInt())
                padding_.top_ = padding_.bottom_ = it3->value.GetInt();
            auto it4 = v_padding.FindMember("bottom");
            if (it4 != v_padding.MemberEnd() && it4->value.IsInt())
                padding_.bottom_ = it4->value.GetInt();
        }

    }
    
    { // 解析title
        auto it = document.FindMember("title");
        if (it != document.MemberEnd() && it->value.IsString())
            title_ = it->value.GetString();
    }
    
    { // 解析position
        auto it = document.FindMember("window-positon");
        if (it != document.MemberEnd() && it->value.IsObject())
        {
            value &v_position = it->value;
            auto it1 = v_position.FindMember("left");
            auto it2 = v_position.FindMember("top");
            if (it1 != v_position.MemberEnd() && it1->value.IsInt())
                window_position_.left_ = it1->value.GetInt();
            if (it2 != v_position.MemberEnd() && it2->value.IsInt())
                window_position_.top_ = it2->value.GetInt();
        }
    }
    
    { // 解析res-dir
        auto it = document.FindMember("res-dir");
        if (it != document.MemberEnd() && it->value.IsString())
        {
            base_url_ = it->value.GetString();
        }
    }
    
    { // 解析board
        auto it = document.FindMember("board");
        if (it != document.MemberEnd() && it->value.IsObject())
        {
            value &v_board = it->value;
            auto it1 = v_board.FindMember("img");
            if (it1 != v_board.MemberEnd() && it1->value.IsString())
                board_.img_url_ = base_url_ + it1->value.GetString();
            auto it2 = v_board.FindMember("background");
            if (it2 != v_board.MemberEnd() && it2->value.IsString())
                board_.background_url_ = base_url_ + it2->value.GetString();
            auto it3 = v_board.FindMember("river-index");
            if(it3 != v_board.MemberEnd() && it3->value.IsInt()) 
                board_.river_index_ = it3->value.GetInt() % 4;
            auto it4 = v_board.FindMember("river-url");
            if(it4 != v_board.MemberEnd() && it4->value.IsString())
                board_.river_url_ = base_url_ + it4->value.GetString();
            auto it5 = v_board.FindMember("box-url");
            if(it5 != v_board.MemberEnd() && it5->value.IsString())
                board_.box_url_ = base_url_ + it5->value.GetString();
        }
    }
    
    { // 解析stone
        std::string text_name = "null";
        auto it = document.FindMember("stone");
        if (it != document.MemberEnd() && it->value.IsObject())
        {
            value &v_stone = it->value;
            auto it1 = v_stone.FindMember("background");
            if (it1 != v_stone.MemberEnd() && it1->value.IsString())
                stone_.background_url_ = base_url_ + it1->value.GetString();
            auto it2 = v_stone.FindMember("text");
            if (it2 != v_stone.MemberEnd() && it2->value.IsString())
                text_name = it2->value.GetString();

            auto it3 = v_stone.FindMember("radius");
            if (it3 != v_stone.MemberEnd() && it3->value.IsInt())
                stone_.radius_ = it3->value.GetInt();
        }

        it = document.FindMember(text_name.c_str());
        if (it != document.MemberEnd() && it->value.IsObject())
        {
            value &v_stone_text = it->value;

            auto it1 = v_stone_text.FindMember("url");
            if (it1 != v_stone_text.MemberEnd() && it1->value.IsString())
                stone_.text_url_ = base_url_ + it1->value.GetString();
            auto it2 = v_stone_text.FindMember("scale");
            if (it2 != v_stone_text.MemberEnd() && it2->value.IsFloat())
                stone_.scale_ = it2->value.GetFloat();
            auto it3 = v_stone_text.FindMember("char-width");
            if (it3 != v_stone_text.MemberEnd() && it3->value.IsInt())
                stone_.char_width_ = it3->value.GetInt();
            // auto it4 = v_stone_text.FindMember("char-height");
            // if (it4 != v_stone_text.MemberEnd() && it4->value.IsInt())
            //     stone_.char_height_ = it4->value.GetInt();
            auto it5 = v_stone_text.FindMember("raw");
            if(it5 != v_stone_text.MemberEnd() && it5->value.IsInt())
                stone_.raw = it5->value.GetInt();
            auto it6 = v_stone_text.FindMember("col");
            if(it6 != v_stone_text.MemberEnd() && it6->value.IsInt())
                stone_.col = it6->value.GetInt();

            auto red_king_index = v_stone_text.FindMember("red-king-index");
            auto red_mandarin_index = v_stone_text.FindMember("red-mandarin-index");
            auto red_bishop_index = v_stone_text.FindMember("red-bishop-index");
            auto red_knight_index = v_stone_text.FindMember("red-knight-index");
            auto red_rook_index = v_stone_text.FindMember("red-rook-index");
            auto red_cannon_index = v_stone_text.FindMember("red-cannon-index");
            auto red_pawn_index = v_stone_text.FindMember("red-pawn-index");

            auto black_king_index = v_stone_text.FindMember("black-king-index");
            auto black_mandarin_index = v_stone_text.FindMember("black-mandarin-index");
            auto black_bishop_index = v_stone_text.FindMember("black-bishop-index");
            auto black_knight_index = v_stone_text.FindMember("black-knight-index");
            auto black_rook_index = v_stone_text.FindMember("black-rook-index");
            auto black_cannon_index = v_stone_text.FindMember("black-cannon-index");
            auto black_pawn_index = v_stone_text.FindMember("black-pawn-index");

            if (red_king_index != v_stone_text.MemberEnd() && red_king_index->value.IsInt())
                stone_.red_king_index_ =
                    red_king_index->value.GetInt();
            if (red_mandarin_index != v_stone_text.MemberEnd() && red_mandarin_index->value.IsInt())
                stone_.red_mandarin_index_ =
                    red_mandarin_index->value.GetInt();
            if (red_bishop_index != v_stone_text.MemberEnd() && red_bishop_index->value.IsInt())
                stone_.red_bishop_index_ =
                    red_bishop_index->value.GetInt();
            if (red_knight_index != v_stone_text.MemberEnd() && red_knight_index->value.IsInt())
                stone_.red_knight_index_ =
                    red_knight_index->value.GetInt();
            if (red_rook_index != v_stone_text.MemberEnd() && red_rook_index->value.IsInt())
                stone_.red_rook_index_ =
                    red_rook_index->value.GetInt();
            if (red_cannon_index != v_stone_text.MemberEnd() && red_cannon_index->value.IsInt())
                stone_.red_cannon_index_ =
                    red_cannon_index->value.GetInt();
            if (red_pawn_index != v_stone_text.MemberEnd() && red_pawn_index->value.IsInt())
                stone_.red_pawn_index_ =
                    red_pawn_index->value.GetInt();

            if (black_king_index != v_stone_text.MemberEnd() && black_king_index->value.IsInt())
                stone_.black_king_index_ =
                    black_king_index->value.GetInt();
            if (black_mandarin_index != v_stone_text.MemberEnd() && black_mandarin_index->value.IsInt())
                stone_.black_mandarin_index_ =
                    black_mandarin_index->value.GetInt();
            if (black_bishop_index != v_stone_text.MemberEnd() && black_bishop_index->value.IsInt())
                stone_.black_bishop_index_ =
                    black_bishop_index->value.GetInt();
            if (black_knight_index != v_stone_text.MemberEnd() && black_knight_index->value.IsInt())
                stone_.black_knight_index_ =
                    black_knight_index->value.GetInt();
            if (black_rook_index != v_stone_text.MemberEnd() && black_rook_index->value.IsInt())
                stone_.black_rook_index_ =
                    black_rook_index->value.GetInt();
            if (black_cannon_index != v_stone_text.MemberEnd() && black_cannon_index->value.IsInt())
                stone_.black_cannon_index_ =
                    black_cannon_index->value.GetInt();
            if (black_pawn_index != v_stone_text.MemberEnd() && black_pawn_index->value.IsInt())
                stone_.black_pawn_index_ =
                    black_pawn_index->value.GetInt();
        }
    
    }
    
    { // 解析icon-url
        auto it = document.FindMember("icon-url");
        if(it != document.MemberEnd() && it->value.IsString()) {
            icon_url_ = base_url_ + it->value.GetString();
        }    
    }
    
    { // 解析侧边栏尺寸
        auto it = document.FindMember("panel-width");
        if(it != document.MemberEnd() && it->value.IsInt()) {
            panel_width_ = it->value.GetInt();
        }

        it = document.FindMember("turn-label-radius");
        if(it != document.MemberEnd() && it->value.IsInt()) {
            turn_label_radius_ = it->value.GetInt();
        }
    }
    
    { // 解析button
        auto it = document.FindMember("button");
        if(it != document.MemberEnd() && it->value.IsObject()) {
            value &v_button = it->value;
            auto it1 = v_button.FindMember("font-url");
            if(it1 != v_button.MemberEnd() && it1->value.IsString())
                button_.font_url_ = base_url_ + it1->value.GetString();
            auto it2 = v_button.FindMember("font-size");
            if(it2 != v_button.MemberEnd() && it2->value.IsInt())
                button_.font_size_ = it2->value.GetInt();
            auto it3 = v_button.FindMember("button-new");
            if(it3 != v_button.MemberEnd() && it3->value.IsString())
                button_.button_new_text_ = it3->value.GetString();
            auto it4 = v_button.FindMember("button-undo");
            if(it4 != v_button.MemberEnd() && it4->value.IsString())
                button_.button_undo_text_ = it4->value.GetString();
        }
    }

    { 
        auto it = document.FindMember("choosen-color");
        if(it != document.MemberEnd() && it->value.IsString() ) {
            std::string msg = it->value.GetString();
            if(msg == "black") choose_red_ = false;
        }
    }
}

Settings::Settings()
{
    assert(p_settings_ == nullptr);
    // 默认构造函数
    padding_.left_ = padding_.right_ = padding_.top_ = padding_.bottom_ = 30;
    window_position_.left_ = 340;
    window_position_.top_ = 5;

    base_url_ = "./resource/";
    
    board_.img_url_ = base_url_ + "img/board.png";
    board_.background_url_ = base_url_ + "img/bg/bg.jpg";
    board_.river_index_ = 0;
    board_.river_url_ = base_url_ + "img/river.png";
    board_.box_url_ = base_url_ + "img/box.png";

    stone_.background_url_ = base_url_ + "img/stone-texture/aerial_wood_snips.png";
    stone_.radius_ = 48;
    stone_.char_width_ = 120;
    // stone_.char_height_ = 122;
    stone_.raw = 1;
    stone_.col = 50;
    stone_.text_url_ = base_url_ + "img/stone-text/xiaozhuan.png";
    stone_.scale_ = 0.6;

    stone_.red_king_index_ = 1;
    stone_.red_mandarin_index_ = 2;
    stone_.red_bishop_index_ = 4;
    stone_.red_knight_index_ = 6;
    stone_.red_rook_index_ = 9;
    stone_.red_cannon_index_ = 11;
    stone_.red_pawn_index_ = 12;

    stone_.black_king_index_ = 0;
    stone_.black_mandarin_index_ = 3;
    stone_.black_bishop_index_ = 5;
    stone_.black_knight_index_ = 7;
    stone_.black_rook_index_ = 8;
    stone_.black_cannon_index_ = 10;
    stone_.black_pawn_index_ = 13;

    title_ = "中國象棋對戰";
    choose_red_ = true;
    icon_url_ = base_url_ + "img/icon.png";
    panel_width_ = 168;
    turn_label_radius_ = 80;

    button_.font_url_ = base_url_ + "font/FZXKJW.TTF";
    button_.font_size_ = 45;

    button_.button_new_text_ = "新开";
    button_.button_undo_text_ = "悔棋";
}

