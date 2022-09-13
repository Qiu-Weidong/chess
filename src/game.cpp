#include "game.h"
#include "settings.h"
#include "asset.h"
#include <iostream>

void Game::run()
{
    while (window_.isOpen())
    {
        processEvent();
        render();
    }
}

void Game::processEvent()
{
    sf::Event event{};

    while (window_.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window_.close();
    }
}

void Game::render()
{
    window_.clear();

    window_.draw(board_background_);
    window_.draw(board_);

    for(const auto &sprite : stone_background_) window_.draw(sprite);
    for(const auto &sprite : stone_text_) window_.draw(sprite);

    window_.display();
}

Game::Game() {
    Settings &settings = Settings::getInstance();
    Asset &asset = Asset::getInstanct();

    // 窗口设置
    const int window_width = settings.stone_.radius_ * 2 * 9 + settings.padding_.left_ + settings.padding_.right_;
    const int window_height = settings.stone_.radius_ * 2 * 10 + settings.padding_.top_ + settings.padding_.bottom_;
    window_.create(sf::VideoMode(window_width, window_height), sf::String::fromUtf8(settings.title_.begin(), settings.title_.end()));
    window_.setPosition(sf::Vector2i(settings.window_position_.left_, settings.window_position_.top_));
    sf::Image icon;
    icon.loadFromFile(settings.icon_url_);
    window_.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // 棋盘设置
    board_.setTexture(asset.getTexture(settings.board_.img_url_));
    sf::Texture &board_bg_texture = asset.getTexture(settings.board_.background_url_);
    float scalex = window_width / (float)board_bg_texture.getSize().x;
    float scaley = window_height / (float)board_bg_texture.getSize().y;
    float scale = scalex > scaley ? scalex : scaley;
    if(scale > 1.0)
        board_background_.setScale(scale, scale);
    board_background_.setTexture(board_bg_texture);

    board_.setPosition(settings.padding_.left_ + settings.stone_.radius_, settings.padding_.top_ + settings.stone_.radius_);
    scale = settings.stone_.radius_ / (board_.getTexture()->getSize().x / 16.0);
    board_.setScale(scale, scale);

    // 棋子设置
    stone_map_.init();
    sf::Texture &stone_bg = asset.getTexture(settings.stone_.background_url_);
    sf::Texture &stone_text = asset.getTexture(settings.stone_.text_url_);

    int x = settings.stone_.char_width_;
    int y = settings.stone_.char_height_;
    sf::IntRect red_king(settings.stone_.red_king_index_ * x, 0, x, y), red_mandarin(settings.stone_.red_mandarin_index_*x, 0, x, y), 
        red_bishop(settings.stone_.red_bishop_index_*x, 0, x, y), red_knight(settings.stone_.red_knight_index_*x,0,x,y), 
        red_rook(settings.stone_.red_rook_index_*x, 0, x, y), red_cannon(settings.stone_.red_cannon_index_*x, 0, x, y), 
        red_pawn(settings.stone_.red_pawn_index_*x, 0, x, y),
        
        black_king(settings.stone_.black_king_index_*x, 0, x, y), black_mandarin(settings.stone_.black_mandarin_index_*x, 0, x, y),
        black_bishop(settings.stone_.black_bishop_index_*x, 0,x,y), black_knight(settings.stone_.black_knight_index_*x, 0, x, y),
        black_rook(settings.stone_.black_rook_index_*x, 0, x, y), black_cannon(settings.stone_.black_cannon_index_*x, 0, x, y),
        black_pawn(settings.stone_.black_pawn_index_*x, 0, x, y) ;

    sf::IntRect rects[] = {
        black_rook, black_knight, black_bishop, black_mandarin, black_king, black_mandarin, black_bishop, black_knight, black_rook,
        black_pawn, black_cannon, black_pawn, black_pawn, black_pawn, black_cannon, black_pawn,
        
        red_pawn, red_cannon, red_pawn, red_pawn, red_pawn, red_cannon, red_pawn,
        red_rook, red_knight, red_bishop, red_mandarin, red_king, red_mandarin, red_bishop, red_knight, red_rook,
    };

    scale = settings.stone_.radius_ / (156.0 / 2.0 ) ;
    for(int i=0; i<StoneMap::stone_cnt_; i++) {
        const int d = 156, cnt = 50;
        stone_background_[i].setTexture(stone_bg);
        stone_background_[i].setTextureRect(sf::IntRect(rand()%cnt*d, 0, d, d));
        stone_background_[i].setScale(scale, scale);
        stone_background_[i].setOrigin(d / 2.0, d / 2.0);
        
        stone_text_[i].setTexture(stone_text);
        stone_text_[i].setTextureRect( settings.choose_red_ ? rects[i] : rects[31 - i]);
        stone_text_[i].setOrigin(settings.stone_.char_width_ / 2.0, settings.stone_.char_height_ / 2.0);
        stone_text_[i].setScale(settings.stone_.scale_, settings.stone_.scale_);

        // 根据棋盘坐标计算实际坐标
        sf::Vector2f pos(stone_map_[i].location_.x * 2 * settings.stone_.radius_ + settings.stone_.radius_ + settings.padding_.left_, 
            stone_map_[i].location_.y * 2 * settings.stone_.radius_ + settings.stone_.radius_ + settings.padding_.top_);
        stone_background_[i].setPosition(pos);
        stone_text_[i].setPosition(pos);

        stone_text_[i].setColor( stone_map_[i].color_ == Stone::StoneColor::Black ? 
            sf::Color(0, 45, 0, 233): sf::Color(145, 0, 0, 233));
    }
}
