#include "game.h"
#include "settings.h"
#include <iostream>

void Game::run()
{
    while (window_.isOpen())
    {
        processEvent();
        render();
    }
}

sf::Texture &Game::getTexture(const std::string &url)
{
    const auto it = textures_.find(url);
    if (it != textures_.end())
        return it->second;
    sf::Texture &texture = textures_[url];
    assert(texture.loadFromFile(url));
    return texture;
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
    window_ << stone_map_;
    window_.display();
}

Game::Game() {
    Settings &settings = Settings::getInstance();

    // 窗口设置
    const int window_width = settings.stone_.radius_ * 2 * 9 + settings.padding_.left_ + settings.padding_.right_;
    const int window_height = settings.stone_.radius_ * 2 * 10 + settings.padding_.top_ + settings.padding_.bottom_;
    window_.create(sf::VideoMode(window_width, window_height), sf::String::fromUtf8(settings.title_.begin(), settings.title_.end()));
    window_.setPosition(sf::Vector2i(settings.window_position_.left_, settings.window_position_.top_));

    // 棋盘设置
    sf::Sprite &board = stone_map_.getBoardSprite();
    board.setTexture(getTexture(settings.board_.img_url_));
    sf::Sprite &board_bg = stone_map_.getBoardBackgroundSprite();
    sf::Texture &board_bg_texture = getTexture(settings.board_.background_url_);
    float scalex = window_width / (float)board_bg_texture.getSize().x;
    float scaley = window_height / (float)board_bg_texture.getSize().y;
    float scale = scalex > scaley ? scalex : scaley;
    if(scale > 1.0)
        board_bg.setScale(scale, scale);
    board_bg.setTexture(board_bg_texture);

    board.setPosition(settings.padding_.left_ + settings.stone_.radius_, settings.padding_.top_ + settings.stone_.radius_);
    scale = settings.stone_.radius_ / (board.getTexture()->getSize().x / 16.0);
    board.setScale(scale, scale);

    // 棋子设置
    sf::Texture &stone_bg = getTexture(settings.stone_.background_url_);
    sf::Texture &stone_text = getTexture(settings.stone_.text_url_);

    int x = settings.stone_.char_width_;
    int y = settings.stone_.char_height_;
    sf::IntRect red_king(settings.stone_.red_king_index_ * x, 0, x, y), red_mandarin(settings.stone_.red_mandarin_index_*x, 0, x, y), 
        red_bishop(settings.stone_.red_bishop_index_*x, 0, x, y), red_knight(settings.stone_.red_knight_index_*x,0,x,y), 
        red_rook(settings.stone_.red_rook_index_*x, 0, x, y), red_cannon(settings.stone_.red_cannon_index_*x, 0, x, y), 
        red_pawn(settings.stone_.red_pawn_index_*x, 0, x, y),
        
        black_king(settings.stone_.black_king_index_*x, 0, x, y), black_mandarin(settings.stone_.black_mandarin_index_*x, 0, x, y),
        black_bishop(settings.stone_.black_bishop_index_*x, 0,x,y), black_knight(settings.stone_.black_knight_index_*x, 0, x, y),
        black_rook(settings.stone_.black_rook_index_*x, 0, x, y), black_cannon(settings.stone_.black_cannon_index_*x, 0, x, y),
        black_pawn(settings.stone_.black_pawn_index_*x, 0, x, y) 
        ;

    sf::IntRect rects[] = {
        red_rook, red_knight, red_bishop, red_mandarin, red_king, red_mandarin, red_bishop, red_knight, red_rook,
        red_pawn, red_cannon, red_pawn, red_pawn, red_pawn, red_cannon, red_pawn,

        black_pawn, black_cannon, black_pawn, black_pawn, black_pawn, black_cannon, black_pawn,
        black_rook, black_knight, black_bishop, black_mandarin, black_king, black_mandarin, black_bishop, black_knight, black_rook,
    };
    sf::Vector2i locations[] = {
        sf::Vector2i(0, 0),
        sf::Vector2i(1, 0),
        sf::Vector2i(2, 0),
        sf::Vector2i(3, 0),
        sf::Vector2i(4, 0),
        sf::Vector2i(5, 0),
        sf::Vector2i(6, 0),
        sf::Vector2i(7, 0),
        sf::Vector2i(8, 0),
        sf::Vector2i(8, 3),
        sf::Vector2i(7, 2),
        sf::Vector2i(6, 3),
        sf::Vector2i(4, 3),
        sf::Vector2i(2, 3),
        sf::Vector2i(1, 2),
        sf::Vector2i(0, 3),

        sf::Vector2i(0, 6),
        sf::Vector2i(1, 7),
        sf::Vector2i(2, 6),
        sf::Vector2i(4, 6),
        sf::Vector2i(6, 6),
        sf::Vector2i(7, 7),
        sf::Vector2i(8, 6),
        sf::Vector2i(8, 9),
        sf::Vector2i(7, 9),
        sf::Vector2i(6, 9),
        sf::Vector2i(5, 9),
        sf::Vector2i(4, 9),
        sf::Vector2i(3, 9),
        sf::Vector2i(2, 9),
        sf::Vector2i(1, 9),
        sf::Vector2i(0, 9),
    };
    Stone::StoneType types[] = {
        Stone::StoneType::Rook, Stone::StoneType::Knight, Stone::StoneType::Bishop, Stone::StoneType::Mandarin,
        Stone::StoneType::King, Stone::StoneType::Mandarin, Stone::StoneType::Bishop, Stone::StoneType::Knight,
        Stone::StoneType::Rook, Stone::StoneType::Pawn, Stone::StoneType::Cannon, Stone::StoneType::Pawn,
        Stone::StoneType::Pawn, Stone::StoneType::Pawn, Stone::StoneType::Cannon, Stone::StoneType::Pawn,

        Stone::StoneType::Pawn, Stone::StoneType::Cannon, Stone::StoneType::Pawn, Stone::StoneType::Pawn, 
        Stone::StoneType::Pawn, Stone::StoneType::Cannon, Stone::StoneType::Pawn, Stone::StoneType::Rook, 
        Stone::StoneType::Knight, Stone::StoneType::Bishop, Stone::StoneType::Mandarin, Stone::StoneType::King, 
        Stone::StoneType::Mandarin, Stone::StoneType::Bishop, Stone::StoneType::Knight, Stone::StoneType::Rook,
    };

    scale = settings.stone_.radius_ / (156.0 / 2.0 ) ;
    for(int i=0; i<StoneMap::stone_cnt_; i++) {
        const int d = 156, cnt = 50;
        stone_map_[i].background_.setTexture(stone_bg);
        stone_map_[i].background_.setTextureRect(sf::IntRect(rand()%cnt*d, 0, d, d));
        stone_map_[i].background_.setScale(scale, scale);
        stone_map_[i].background_.setOrigin(d / 2.0, d / 2.0);
        
        stone_map_[i].text_.setTexture(stone_text);
        stone_map_[i].text_.setTextureRect(rects[i]);
        stone_map_[i].text_.setOrigin(settings.stone_.char_width_ / 2.0, settings.stone_.char_height_ / 2.0);
        stone_map_[i].text_.setScale(settings.stone_.scale_, settings.stone_.scale_);

        stone_map_[i].up_or_down_ = i < (int)Stone::StoneID::DownPawnLeft ? Stone::UpOrDown::Up : Stone::UpOrDown::Down;
        stone_map_[i].alive_ = true;
        stone_map_[i].color_ = i < (int)Stone::StoneID::DownPawnLeft ? Stone::StoneColor::Black : Stone::StoneColor::Red;
        stone_map_[i].location_ = locations[i];
        stone_map_[i].stone_type_ = types[i];

        // 根据棋盘坐标计算实际坐标
        sf::Vector2f pos(locations[i].x * 2 * settings.stone_.radius_ + settings.stone_.radius_, 
            locations[i].y * 2 * settings.stone_.radius_ + settings.stone_.radius_);
        stone_map_[i].background_.setPosition(pos);
        stone_map_[i].text_.setPosition(pos);
    }


    
}
