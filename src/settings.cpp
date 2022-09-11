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

    /// 解析padding
    value &v_padding = document["padding"];
    if (!v_padding.IsNull() && v_padding.IsObject())
    {
        value &v_left = v_padding["left"];
        value &v_right = v_padding["right"];
        value &v_top = v_padding["top"];
        value &v_bottom = v_padding["bottom"];

        if (!v_left.IsNull() && v_left.IsInt())
            padding_.left_ = v_left.GetInt();
        if (!v_right.IsNull() && v_right.IsInt())
            padding_.right_ = v_right.GetInt();
        if (!v_top.IsNull() && v_top.IsInt())
            padding_.top_ = v_top.GetInt();
        if (!v_top.IsNull() && v_top.IsInt())
            padding_.bottom_ = v_top.GetInt();
    }

    value &v_title = document["title"];
    if (!v_title.IsNull() && v_title.IsString())
        title_ = v_title.GetString();
    value &v_position = document["window-position"];
    if (!v_position.IsNull() && v_position.IsObject())
    {
        value &v_left = v_position["left"];
        if (!v_left.IsNull() && v_left.IsInt())
            window_position_.left_ = v_left.GetInt();
        value &v_top = v_position["top"];
        if (!v_top.IsNull() && v_top.IsInt())
            window_position_.top_ = v_top.GetInt();
    }

    value &v_base_url = document["img-dir"];
    if (!v_base_url.IsNull() && v_base_url.IsString())
        base_url_ = v_base_url.GetString();
    value &v_board = document["board"];
    if (!v_board.IsNull() && v_board.IsObject())
    {
        value &v_img_url = v_board["img"];
        value &v_background_url = v_board["background"];
        if (!v_img_url.IsNull() && v_img_url.IsString())
            board_.img_url_ = base_url_ + v_img_url.GetString();
        if (!v_background_url.IsNull() && v_background_url.IsString())
            board_.background_url_ = base_url_ + v_background_url.GetString();
    }

    value &v_stone = document["stone"];
    std::string text_name = "none";
    if (!v_stone.IsNull() && v_stone.IsObject())
    {
        value &v_background_url = v_stone["background"];
        if (!v_background_url.IsNull() && v_background_url.IsString())
            stone_.background_url_ = base_url_ + v_background_url.GetString();
        value &v_text = v_stone["text"];
        if (!v_text.IsNull() && v_text.IsString())
            text_name = v_text.GetString();

        value &v_stone_radius = v_stone["radius"];
        if (!v_stone_radius.IsNull() && v_stone_radius.IsInt())
            stone_.radius_ = v_stone_radius.GetInt();
    }

    value &v_stone_text = document[text_name.c_str()];
    if (!v_stone_text.IsNull() && v_stone_text.IsObject())
    {
        value &v_url = v_stone_text["url"];
        if (!v_url.IsNull() && v_url.IsString())
            stone_.text_url_ = base_url_ + v_url.GetString();
        value &v_scale = v_stone_text["scale"];
        if (!v_scale.IsNull() && v_scale.IsFloat())
            stone_.scale_ = v_scale.GetFloat();
        value &v_char_width = v_stone_text["char-widht"];
        value &v_char_height = v_stone_text["char-height"];
        if (!v_char_width.IsNull() && v_char_width.IsInt())
            stone_.char_width_ =
                v_char_width.GetInt();
        if (!v_char_height.IsNull() && v_char_height.IsInt())
            stone_.char_height_ =
                v_char_height.GetInt();

        value &v_red_king_index = v_stone_text["red-king-index"];
        value &v_red_mandarin_index = v_stone_text["red-mandarin-index"];
        value &v_red_bishop_index = v_stone_text["red-bishop-index"];
        value &v_red_knight_index = v_stone_text["red-knight-index"];
        value &v_red_rook_index = v_stone_text["red-rook-index"];
        value &v_red_cannon_index = v_stone_text["red-cannon-index"];
        value &v_red_pawn_index = v_stone_text["red-pawn-index"];

        value &v_black_king_index = v_stone_text["black-king-index"];
        value &v_black_mandarin_index = v_stone_text["black-mandarin-index"];
        value &v_black_bishop_index = v_stone_text["black-bishop-index"];
        value &v_black_knight_index = v_stone_text["black-knight-index"];
        value &v_black_rook_index = v_stone_text["black-rook-index"];
        value &v_black_cannon_index = v_stone_text["black-cannon-index"];
        value &v_black_pawn_index = v_stone_text["black-pawn-index"];

        if (!v_red_king_index.IsNull() && v_red_king_index.IsInt())
            stone_.red_king_index_ =
                v_red_king_index.GetInt();
        if (!v_red_mandarin_index.IsNull() && v_red_mandarin_index.IsInt())
            stone_.red_mandarin_index_ =
                v_red_mandarin_index.GetInt();
        if (!v_red_bishop_index.IsNull() && v_red_bishop_index.IsInt())
            stone_.red_bishop_index_ =
                v_red_bishop_index.GetInt();
        if (!v_red_knight_index.IsNull() && v_red_knight_index.IsInt())
            stone_.red_knight_index_ =
                v_red_knight_index.GetInt();
        if (!v_red_rook_index.IsNull() && v_red_rook_index.IsInt())
            stone_.red_rook_index_ =
                v_red_rook_index.GetInt();
        if (!v_red_cannon_index.IsNull() && v_red_cannon_index.IsInt())
            stone_.red_cannon_index_ =
                v_red_cannon_index.GetInt();
        if (!v_red_pawn_index.IsNull() && v_red_pawn_index.IsInt())
            stone_.red_pawn_index_ =
                v_red_pawn_index.GetInt();

        if (!v_black_king_index.IsNull() && v_black_king_index.IsInt())
            stone_.black_king_index_ =
                v_black_king_index.GetInt();
        if (!v_black_mandarin_index.IsNull() && v_black_mandarin_index.IsInt())
            stone_.black_mandarin_index_ =
                v_black_mandarin_index.GetInt();
        if (!v_black_bishop_index.IsNull() && v_black_bishop_index.IsInt())
            stone_.black_bishop_index_ =
                v_black_bishop_index.GetInt();
        if (!v_black_knight_index.IsNull() && v_black_knight_index.IsInt())
            stone_.black_knight_index_ =
                v_black_knight_index.GetInt();
        if (!v_black_rook_index.IsNull() && v_black_rook_index.IsInt())
            stone_.black_rook_index_ =
                v_black_rook_index.GetInt();
        if (!v_black_cannon_index.IsNull() && v_black_cannon_index.IsInt())
            stone_.black_cannon_index_ =
                v_black_cannon_index.GetInt();
        if (!v_black_pawn_index.IsNull() && v_black_pawn_index.IsInt())
            stone_.black_pawn_index_ =
                v_black_pawn_index.GetInt();
    }
}

Settings::Settings()
{
    // 默认构造函数
    padding_.left_ = padding_.right_ = padding_.top_ = padding_.bottom_ = 30;
    window_position_.left_ = 340;
    window_position_.top_ = 5;

    base_url_ = "./resource/img/";
    board_.img_url_ = base_url_ + "board.png";
    board_.background_url_ = base_url_ + "bg/bg.jpg";
    stone_.background_url_ = base_url_ + "stone-texture/aerial_wood_snips.png";
    stone_.radius_ = 46;
    stone_.char_width_ = 121;
    stone_.char_height_ = 122;
    stone_.text_url_ = base_url_ + "stone-text/xiaozhuan.png";
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
}