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
        switch(event.type) {
            case sf::Event::Closed:
                window_.close();
                break;
            case sf::Event::MouseButtonPressed:
                mouseClickedHandler(event);
                break;
            case sf::Event::MouseMoved:
                mouseMoveHandler(event);
                break;
            default:
                break;
        }
    }
}

void Game::render()
{
    window_.clear();

    window_.draw(board_background_);
    window_.draw(board_);
    window_.draw(river_);

    for(const auto &sprite : stone_background_) window_.draw(sprite);
    for(const auto &sprite : stone_text_) window_.draw(sprite);

    window_.draw(box_from_);
    window_.draw(box_to_);
    window_.draw(box_select_);
    window_.draw(turn_label_background_);

    if(stone_map_.getTurn() == Stone::StoneColor::Red)
        window_.draw(turn_label_red_);
    else window_.draw(turn_label_black_);

    window_.draw(new_game_button_);
    window_.draw(undo_button_);

    window_.draw(looog_);
    window_.draw(win_);

    window_.display();
}

Game::Game() {
    Settings &settings = Settings::getInstance();
    Asset &asset = Asset::getInstanct();

    // 一些初始化常量设置
    const int window_width = settings.stone_.radius_ * 2 * 9 + settings.padding_.left_ + settings.padding_.right_ + settings.panel_width_;
    const int window_height = settings.stone_.radius_ * 2 * 10 + settings.padding_.top_ + settings.padding_.bottom_;
    const sf::Texture &stone_bg = asset.getTexture(settings.stone_.background_url_);
    const sf::Texture &stone_text = asset.getTexture(settings.stone_.text_url_);
    const int x = settings.stone_.char_width_;
    const int y = stone_text.getSize().y;
    const sf::IntRect red_king(settings.stone_.red_king_index_ * x, 0, x, y), red_mandarin(settings.stone_.red_mandarin_index_*x, 0, x, y), 
        red_bishop(settings.stone_.red_bishop_index_*x, 0, x, y), red_knight(settings.stone_.red_knight_index_*x,0,x,y), 
        red_rook(settings.stone_.red_rook_index_*x, 0, x, y), red_cannon(settings.stone_.red_cannon_index_*x, 0, x, y), 
        red_pawn(settings.stone_.red_pawn_index_*x, 0, x, y),
        
        black_king(settings.stone_.black_king_index_*x, 0, x, y), black_mandarin(settings.stone_.black_mandarin_index_*x, 0, x, y),
        black_bishop(settings.stone_.black_bishop_index_*x, 0,x,y), black_knight(settings.stone_.black_knight_index_*x, 0, x, y),
        black_rook(settings.stone_.black_rook_index_*x, 0, x, y), black_cannon(settings.stone_.black_cannon_index_*x, 0, x, y),
        black_pawn(settings.stone_.black_pawn_index_*x, 0, x, y) ;
    const sf::IntRect rects[] = {
        black_rook, black_knight, black_bishop, black_mandarin, black_king, black_mandarin, black_bishop, black_knight, black_rook,
        black_pawn, black_cannon, black_pawn, black_pawn, black_pawn, black_cannon, black_pawn,
        
        red_pawn, red_cannon, red_pawn, red_pawn, red_pawn, red_cannon, red_pawn,
        red_rook, red_knight, red_bishop, red_mandarin, red_king, red_mandarin, red_bishop, red_knight, red_rook,
    };
    const sf::Color black(0, 45, 0, 233), red(145, 0, 0, 233);
    
    { // 窗口及图标设置
        window_.create(sf::VideoMode(window_width, window_height), sf::String::fromUtf8(settings.title_.begin(), settings.title_.end()), 
            sf::Style::Close | sf::Style::Titlebar  );
        window_.setPosition(sf::Vector2i(settings.window_position_.left_, settings.window_position_.top_));    
        sf::Image icon;
        icon.loadFromFile(settings.icon_url_);
        window_.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    
    { // 棋盘设置
        board_.setTexture(asset.getTexture(settings.board_.img_url_));
        sf::Texture &board_bg_texture = asset.getTexture(settings.board_.background_url_);
        float scalex = window_width / (float)board_bg_texture.getSize().x;
        float scaley = window_height / (float)board_bg_texture.getSize().y;
        float scale = scalex > scaley ? scalex : scaley;
        if(scale > 1.0 || scale < 0.5)
            board_background_.setScale(scale, scale);
        board_background_.setTexture(board_bg_texture);

        board_.setPosition(settings.padding_.left_ + settings.stone_.radius_, settings.padding_.top_ + settings.stone_.radius_);
        scale = settings.stone_.radius_ / (board_.getTexture()->getSize().x / 16.0);
        board_.setScale(scale, scale);

        sf::Texture &river_texture = asset.getTexture(settings.board_.river_url_);
        int river_height = river_texture.getSize().y / 4;
        river_.setTexture(river_texture);
        river_.setTextureRect(sf::IntRect(0, river_height * settings.board_.river_index_, river_texture.getSize().x, river_height));
        river_.setOrigin(river_texture.getSize().x / 2.0, river_height / 2.0);
        river_.setPosition((window_width - settings.panel_width_) / 2.0, window_height / 2.0);
        river_.setColor(sf::Color(45, 45, 45, 127));
        scale = settings.stone_.radius_ * 2.0 / (float)river_height;
        river_.setScale(scale, scale);   
    }
    
    { // 棋子设置
        stone_map_.init();
        const int d = stone_bg.getSize().y / settings.stone_.raw, raw = settings.stone_.raw, col = settings.stone_.col;
        float scale = settings.stone_.radius_ / (d / 2.0 ) ;

        for(int i=0; i<StoneMap::stone_cnt_; i++) {
            
            stone_background_[i].setTexture(stone_bg);
            stone_background_[i].setTextureRect(sf::IntRect(rand()%col*d, rand()%raw*d, d, d));
            stone_background_[i].setScale(scale, scale);
            stone_background_[i].setOrigin(d / 2.0, d / 2.0);
            
            stone_text_[i].setTexture(stone_text);
            stone_text_[i].setTextureRect( settings.choose_red_ ? rects[i] : rects[31 - i]);
            stone_text_[i].setOrigin(settings.stone_.char_width_ / 2.0, y / 2.0);
            stone_text_[i].setScale(settings.stone_.scale_, settings.stone_.scale_);

            // 根据棋盘坐标计算实际坐标
            sf::Vector2f pos(stone_map_[i].location_.x * 2 * settings.stone_.radius_ + settings.stone_.radius_ + settings.padding_.left_, 
                stone_map_[i].location_.y * 2 * settings.stone_.radius_ + settings.stone_.radius_ + settings.padding_.top_);
            stone_background_[i].setPosition(pos);
            stone_text_[i].setPosition(pos);

            stone_text_[i].setColor( stone_map_[i].color_ == Stone::StoneColor::Black ? 
                black: red);
        }
    }
    
    { // 选择框设置
        sf::Texture &box = asset.getTexture(settings.board_.box_url_);
        float scale =  (float) (settings.stone_.radius_ << 1) / box.getSize().x;
        box_select_.setTexture(box);
        box_from_.setTexture(box);
        box_to_.setTexture(box);
        box_select_.setScale(scale, scale);
        box_from_.setScale(scale, scale);
        box_to_.setScale(scale, scale);
        box_select_.setOrigin(box.getSize().x >> 1, box.getSize().y >> 1);
        box_from_.setOrigin(box.getSize().x >> 1, box.getSize().y >> 1);
        box_to_.setOrigin(box.getSize().x >> 1, box.getSize().y >> 1);

        box_select_.setPosition(-settings.stone_.radius_, 0);
        box_from_.setPosition(-settings.stone_.radius_, 0);
        box_to_.setPosition(-settings.stone_.radius_, 0);

        box_from_.setColor(sf::Color(255, 0, 0, 213));
        box_select_.setColor(sf::Color(233, 128, 24, 213));
        box_to_.setColor(sf::Color(15, 234, 255, 213));
    }
    
    { // 当前玩家标签
        const int d = stone_bg.getSize().y / settings.stone_.raw, raw = settings.stone_.raw, col = settings.stone_.col;
        const int turn_label_left = (settings.panel_width_ >> 1);
        const int pos_x = window_width - settings.panel_width_ + turn_label_left;
        const int pos_y = settings.turn_label_radius_ + settings.padding_.top_ + settings.stone_.radius_ * 2;
        turn_label_background_.setTexture(stone_bg);
        turn_label_background_.setTextureRect(sf::IntRect(rand()%col*d, rand()%raw*d, d, d));
        turn_label_background_.setOrigin(d / 2.0, d / 2.0);
        turn_label_background_.setPosition(pos_x, pos_y);
        
        turn_label_black_.setTexture(stone_text);
        turn_label_red_.setTexture(stone_text);

        turn_label_black_.setTextureRect(black_king);
        turn_label_red_.setTextureRect(red_king);
        turn_label_black_.setColor(black);
        turn_label_red_.setColor(red);

        turn_label_black_.setOrigin(settings.stone_.char_width_ / 2.0, y / 2.0);
        turn_label_red_.setOrigin(settings.stone_.char_width_ / 2.0, y / 2.0);
        turn_label_black_.setPosition(pos_x, pos_y);
        turn_label_red_.setPosition(pos_x, pos_y);
    }
    
    { // 控制按钮
        sf::Font &font = asset.getFont(settings.button_.font_url_);
        new_game_button_.setFont(font);
        undo_button_.setFont(font);
        new_game_button_.setString(sf::String::fromUtf8(settings.button_.button_new_text_.begin(), settings.button_.button_new_text_.end()));
        undo_button_.setString(sf::String::fromUtf8(settings.button_.button_undo_text_.begin(), settings.button_.button_undo_text_.end()));

        new_game_button_.setFillColor(sf::Color::Black);
        undo_button_.setFillColor(sf::Color::Black);

        new_game_button_.setCharacterSize(settings.button_.font_size_);
        undo_button_.setCharacterSize(settings.button_.font_size_);

        sf::FloatRect bound = new_game_button_.getLocalBounds();
        new_game_button_.setOrigin(bound.width / 2.0, bound.height);
        new_game_button_.setPosition(window_width - settings.panel_width_ / 2, window_height / 2);

        bound = undo_button_.getLocalBounds();
        undo_button_.setOrigin(bound.width / 2.0, 0);
        undo_button_.setPosition(window_width - settings.panel_width_ / 2, window_height / 2);

        // new_game_button_.setStyle(sf::Text::Bold );
        // new_game_button_.setColor(sf::Color::Blue); // 已经弃用
        // new_game_button_.setOutlineColor(sf::Color::Blue);
        // new_game_button_.setOutlineThickness(1);
    }

    {
        sf::Texture &texture = asset.getTexture(settings.base_url_ + "img/long.png");
        looog_.setTexture(texture);
        looog_.setOrigin(258.0, 285.0);
        looog_.setPosition((window_width - settings.panel_width_) / 2.0, window_height / 2.0);
        looog_.setColor(sf::Color(127, 27, 27, 175));

        sf::Texture &texture2 = asset.getTexture(settings.win_url_);
        win_.setTexture(texture2);
        win_.setOrigin(texture2.getSize().x / 2.0, texture2.getSize().y / 2.0);
        win_.setPosition((window_width - settings.panel_width_) / 2.0, window_height / 2.0);
        win_.setColor(sf::Color(155, 27, 27, 225));
    }
    

}

void Game::mouseClickedHandler(const sf::Event &event)
{
    if(event.mouseButton.button != sf::Mouse::Button::Left) return; // 暂时先不处理鼠标右键
    int x = event.mouseButton.x;
    int y = event.mouseButton.y;
    // 计算点击的棋盘坐标
    Settings &settings = Settings::getInstance();
    const int r = settings.stone_.radius_;
    
    // 点击到棋盘外面
    if(x < settings.padding_.left_ || x > settings.padding_.left_ + r * 18 + settings.padding_.left_
        || y < settings.padding_.top_ || y > settings.padding_.top_ + r * 20)
    {
        // 查看是否点击了按钮
        if(new_game_button_.getGlobalBounds().contains(x, y)) {
            stone_map_.init();
            updateStones();
        }
        else if(undo_button_.getGlobalBounds().contains(x, y)) {
            stone_map_.regret();
            updateStones();
        }
        return ;
    }

    
    int board_x = (x - settings.padding_.left_) / (r << 1);
    int board_y = (y - settings.padding_.top_) / (r << 1);

    int cx = board_x * (r << 1) + settings.padding_.left_ + r;
    int cy = board_y * (r << 1) + settings.padding_.top_ + r;

    if((x - cx) * (x - cx) + (y - cy) * (y - cy) < r * r)
    {
        stone_map_.onBoardClicked(board_x, board_y);
        updateStones();
    }
        
}

void Game::mouseMoveHandler(const sf::Event &event) {
    Settings &settings = Settings::getInstance();
    int x = event.mouseMove.x, y = event.mouseMove.y;

    if(new_game_button_.getGlobalBounds().contains(x, y)) {
        new_game_button_.setCharacterSize(settings.button_.font_size_ * 1.25);
    }
    else {
        new_game_button_.setCharacterSize(settings.button_.font_size_);
    }

    if(undo_button_.getGlobalBounds().contains(x, y)) {
        undo_button_.setCharacterSize(settings.button_.font_size_ * 1.25);
    }
    else {
        undo_button_.setCharacterSize(settings.button_.font_size_ );
    }

    const int window_width = settings.stone_.radius_ * 2 * 9 + settings.padding_.left_ + settings.padding_.right_ + settings.panel_width_;
    const int window_height = settings.stone_.radius_ * 2 * 10 + settings.padding_.top_ + settings.padding_.bottom_;
    sf::FloatRect bound = new_game_button_.getLocalBounds();
    new_game_button_.setOrigin(bound.width / 2.0, bound.height);
    new_game_button_.setPosition(window_width - settings.panel_width_ / 2, window_height / 2);

    bound = undo_button_.getLocalBounds();
    undo_button_.setOrigin(bound.width / 2.0, 0);
    undo_button_.setPosition(window_width - settings.panel_width_ / 2, window_height / 2);
}

void Game::openNewGame() {
    stone_map_.init();
    updateStones();
}

void Game::updateStones() {
    Settings &settings = Settings::getInstance();

    // 更新box
    if(stone_map_.getSelectedStone() != nullptr) {
        // 选中某个棋子
        Stone *selected = stone_map_.getSelectedStone();
        sf::Vector2f pos(selected->location_.x*(settings.stone_.radius_ << 1) + settings.padding_.left_ + settings.stone_.radius_, 
                selected->location_.y*(settings.stone_.radius_ << 1) + settings.padding_.top_ + settings.stone_.radius_);
        box_select_.setPosition(pos);
    }
    else {
        box_select_.setPosition(-settings.stone_.radius_, -settings.stone_.radius_);
    }

    sf::Vector2f from_pos(stone_map_.from_.x*(settings.stone_.radius_ << 1) + settings.padding_.left_ + settings.stone_.radius_, 
                stone_map_.from_.y*(settings.stone_.radius_ << 1) + settings.padding_.top_ + settings.stone_.radius_ );
    box_from_.setPosition(from_pos);
    sf::Vector2f to_pos(stone_map_.to_.x*(settings.stone_.radius_ << 1) + settings.padding_.left_ + settings.stone_.radius_, 
                stone_map_.to_.y*(settings.stone_.radius_ << 1) + settings.padding_.top_ + settings.stone_.radius_ );
    box_to_.setPosition(to_pos);
    // 更新棋子坐标
    for(int i=0; i<StoneMap::stone_cnt_; i++) {
        if(! stone_map_[i].alive_) {
            stone_background_[i].setPosition(-settings.stone_.radius_, -settings.stone_.radius_);
            stone_text_[i].setPosition(-settings.stone_.radius_, -settings.stone_.radius_);
        }
        else {
            sf::Vector2f pos(stone_map_[i].location_.x*(settings.stone_.radius_ << 1) + settings.padding_.left_ + settings.stone_.radius_, 
                stone_map_[i].location_.y*(settings.stone_.radius_ << 1) + settings.padding_.top_ + settings.stone_.radius_);
            stone_background_[i].setPosition(pos);
            stone_text_[i].setPosition(pos);
        }
    }
}
