#ifndef CHESS_SETTINGS_H_
#define CHESS_SETTINGS_H_
#include <string>
#include <fstream>
// 将读取settings.json中的数据
// 采用单例模式

struct Settings {
    struct {
        int left_, right_, top_, bottom_;
    } padding_;

    struct {
        int left_, top_;
    } window_position_;
    struct {
        int width, height;
    } window_size_;
    struct {
        std::string img_url_, background_url_;
        int river_index_;
        std::string river_url_, box_url_;
    } board_;
    struct {
        std::string background_url_;
        std::string text_url_;
        float scale_;
        int char_width_;
        int radius_;
        int red_mandarin_index_, red_king_index_, 
            red_bishop_index_, red_knight_index_,
            red_rook_index_, red_cannon_index_,
            red_pawn_index_,

            black_mandarin_index_, black_king_index_, 
            black_bishop_index_, black_knight_index_,
            black_rook_index_, black_cannon_index_,
            black_pawn_index_; 
        int raw, col;
    } stone_;
    std::string title_;
    std::string base_url_;
    std::string icon_url_;
    std::string win_url_, lose_url_;

    struct {
        std::string font_url_, button_new_text_, button_undo_text_;
        int font_size_;
    } button_;
    
    bool choose_red_;
    int panel_width_;
    int turn_label_radius_;

    void loadFromFile(std::ifstream &in);
    static Settings &getInstance() {
        if(p_settings_ == nullptr) p_settings_ = new Settings();
        return *p_settings_;
    }

    friend std::ostream &operator<<(std::ostream &os, const Settings &settings) {
        os << "padding: {\n" 
            << "\tleft: " << settings.padding_.left_ << ",\n"
            << "\tright: "<< settings.padding_.right_ << ",\n"
            << "\ttop: " << settings.padding_.top_ << ",\n"
            << "\tbottom: " << settings.padding_.bottom_ << ",\n"
        << "},\n"
        << "window-position: {\n"
            << "\tleft: " << settings.window_position_.left_ << ",\n"
            << "\ttop: " << settings.window_position_.top_ << ",\n"
        << "},\n"
        << "board:{\n"
            << "\timg: " << settings.board_.img_url_ << ",\n"
            << "\tbackground: " << settings.board_.background_url_ << ",\n"
        << "},\n"
        << "stone: {\n"
            << "\tbackground: " << settings.stone_.background_url_ << ",\n"
            << "\tradius: " << settings.stone_.radius_ << ",\n"
        << "},\n"

        ;
        return os;
    }
private:
    static Settings * p_settings_;
    Settings();

    Settings(const Settings &) = delete;
    Settings(Settings &&) = delete;
    Settings &operator=(const Settings &) = delete;
    Settings &operator=(Settings &&) = delete;
};

#endif // CHESS_SETTINGS_H_
