#include "game.h"
#include "settings.h"
#include <iostream>

// void Game::initFromFile(std::ifstream &in)
// {
//     rapidjson::IStreamWrapper isw(in);
//     rapidjson::Document document;
//     document.ParseStream(isw);

//     initWindow(document);
//     initStoneMap(document);


    // rapidjson::Value &stone_text_value = document["stone-text"];
    // std::string stone_text = stone_text_value.IsNull() ? "jinwen" : stone_text_value.GetString();
    // rapidjson::Value &stone_text_value2 = document[stone_text.c_str()];
    // std::string stone_text_url = url + stone_text_value2["url"].GetString();
    // float text_scale = stone_text_value2["scale"].GetFloat();
    // rapidjson::Value &red_value = stone_text_value2["red"];
    // rapidjson::Value &black_value = stone_text_value2["black"];

    // rapidjson::Value &red_king_value = red_value["king"];
    // sf::IntRect red_king(red_king_value["left"].GetInt(), red_king_value["top"].GetInt(), 
    //     red_king_value["width"].GetInt(), red_king_value["height"].GetInt());

    // rapidjson::Value &red_mandarin_value = red_value["mandarin"];
    // sf::IntRect red_mandarin(red_mandarin_value["left"].GetInt(), red_mandarin_value["top"].GetInt(), 
    //     red_mandarin_value["width"].GetInt(), red_mandarin_value["height"].GetInt());

    // rapidjson::Value &red_bishop_value = red_value["bishop"];
    // sf::IntRect red_bishop(red_bishop_value["left"].GetInt(), red_bishop_value["top"].GetInt(), 
    //     red_bishop_value["width"].GetInt(), red_bishop_value["height"].GetInt());

    // rapidjson::Value &red_knight_value = red_value["knight"];
    // sf::IntRect red_knight(red_knight_value["left"].GetInt(), red_knight_value["top"].GetInt(), 
    //     red_knight_value["width"].GetInt(), red_knight_value["height"].GetInt());
    // rapidjson::Value &red_rook_value = red_value["rook"];
    // sf::IntRect red_rook(red_rook_value["left"].GetInt(), red_rook_value["top"].GetInt(), 
    //     red_rook_value["width"].GetInt(), red_rook_value["height"].GetInt());
    // rapidjson::Value &red_cannon_value = red_value["cannon"];
    // sf::IntRect red_cannon(red_cannon_value["left"].GetInt(), red_cannon_value["top"].GetInt(), 
    //     red_cannon_value["width"].GetInt(), red_cannon_value["height"].GetInt());
    // rapidjson::Value &red_pawn_value = red_value["pawn"];
    // sf::IntRect red_pawn(red_pawn_value["left"].GetInt(), red_pawn_value["top"].GetInt(), 
    //     red_pawn_value["width"].GetInt(), red_pawn_value["height"].GetInt());

    // rapidjson::Value &black_king_value = black_value["king"];
    // sf::IntRect black_king(black_king_value["left"].GetInt(), black_king_value["top"].GetInt(), 
    //     black_king_value["width"].GetInt(), black_king_value["height"].GetInt());

    // rapidjson::Value &black_mandarin_value = black_value["mandarin"];
    // sf::IntRect black_mandarin(black_mandarin_value["left"].GetInt(), black_mandarin_value["top"].GetInt(), 
    //     black_mandarin_value["width"].GetInt(), black_mandarin_value["height"].GetInt());

    // rapidjson::Value &black_bishop_value = black_value["bishop"];
    // sf::IntRect black_bishop(black_bishop_value["left"].GetInt(), black_bishop_value["top"].GetInt(), 
    //     black_bishop_value["width"].GetInt(), black_bishop_value["height"].GetInt());

    // rapidjson::Value &black_knight_value = black_value["knight"];
    // sf::IntRect black_knight(black_knight_value["left"].GetInt(), black_knight_value["top"].GetInt(), 
    //     black_knight_value["width"].GetInt(), black_knight_value["height"].GetInt());
    // rapidjson::Value &black_rook_value = black_value["rook"];
    // sf::IntRect black_rook(black_rook_value["left"].GetInt(), black_rook_value["top"].GetInt(), 
    //     black_rook_value["width"].GetInt(), black_rook_value["height"].GetInt());
    // rapidjson::Value &black_cannon_value = black_value["cannon"];
    // sf::IntRect black_cannon(black_cannon_value["left"].GetInt(), black_cannon_value["top"].GetInt(), 
    //     black_cannon_value["width"].GetInt(), black_cannon_value["height"].GetInt());
    // rapidjson::Value &black_pawn_value = black_value["pawn"];
    // sf::IntRect black_pawn(black_pawn_value["left"].GetInt(), black_pawn_value["top"].GetInt(), 
    //     black_pawn_value["width"].GetInt(), black_pawn_value["height"].GetInt());

    // rapidjson::Value &stone_texture_value = document["stone-texture"];
    // std::string stone_texture_url = url + (stone_texture_value.IsNull() ? "stone-texture/aerial_wood_snips.png" : stone_texture_value.GetString() );
    // sf::Texture &stone_texture = getTexture(stone_texture_url);
    // sf::Texture &stone_text_texture = getTexture(stone_text_url);


    // sf::IntRect rects[] = {
        

    //     black_rook, black_knight, black_bishop, black_mandarin, black_king, black_mandarin, black_bishop, black_knight, black_rook,
    //     black_pawn, black_cannon, black_pawn, black_pawn, black_pawn, black_cannon, black_pawn, 
        
    //     red_pawn, red_cannon, red_pawn, red_pawn, red_pawn, red_cannon, red_pawn, 
    //     red_rook, red_knight, red_bishop, red_mandarin, red_king, red_mandarin, red_bishop, red_knight, red_rook,
        
    // };

    // for(int i=0; i<StoneMap::stone_cnt_; i++) {
    //     stone_background_sprites_[i].setTexture(stone_texture);
    //     stone_background_sprites_[i].setTextureRect(sf::IntRect(rand()%50*156, 0, 156, 156));
    //     stone_background_sprites_[i].setOrigin(156/2.0, 156/2.0);
    //     float scale = stone_radius / (156/2.0);
    //     stone_background_sprites_[i].setScale(scale, scale);

    //     // 根据stonemap来初始化位置
    //     sf::Vector2i location = stone_map_[i].getLocation();
    //     stone_background_sprites_[i].setPosition(padding_left + stone_radius + location.x*stone_radius*2, 
    //         location.y*stone_radius*2+ padding_left + stone_radius);
        
        
    //     stone_text_sprites_[i].setTexture(stone_text_texture);
    //     stone_text_sprites_[i].setTextureRect(rects[i]);
    //     stone_text_sprites_[i].setOrigin(121/2.0, 157/2.0);
    //     stone_text_sprites_[i].setScale(text_scale, text_scale);
    //     stone_text_sprites_[i].setPosition(padding_left + stone_radius + location.x*stone_radius*2, 
    //         location.y*stone_radius*2+ padding_left + stone_radius);
    // }


// }

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
    // assert(texture.loadFromFile(url));
    texture.loadFromFile(url);
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


// 初始化函数
// void Game::initWindow(rapidjson::Document & document)
// {
//     // 先给出一些默认值
//     int padding_left = 30, padding_top = 30, padding_right=30, padding_bottom=30, stone_radius=46;


Game::Game() {
    Settings &settings = Settings::getInstance();

    
    const int window_width = settings.stone_.radius_ * 2 * 9 + settings.padding_.left_ + settings.padding_.right_;
    const int window_height = settings.stone_.radius_ * 2 * 10 + settings.padding_.top_ + settings.padding_.bottom_;
    window_.create(sf::VideoMode(window_width, window_height), sf::String::fromUtf8(settings.title_.begin(), settings.title_.end()));

    window_.setPosition(sf::Vector2i(settings.window_position_.left_, settings.window_position_.top_));
    
    sf::Sprite &board = stone_map_.getBoardSprite();
    board.setTexture(getTexture(settings.board_.img_url_));
    sf::Sprite &board_bg = stone_map_.getBoardBackgroundSprite();
    board_bg.setTexture(getTexture(settings.board_.background_url_));


    board.setPosition(settings.padding_.left_ + settings.stone_.radius_, settings.padding_.top_ + settings.stone_.radius_);
    float scale = settings.stone_.radius_ / (board.getTexture()->getSize().x / 16.0);
    board.setScale(scale, scale);

    sf::Texture &stone_bg = getTexture(settings.stone_.background_url_);
    sf::Texture &stone_text = getTexture(settings.stone_.text_url_);

    for(int i=0; i<StoneMap::stone_cnt_; i++) {
        const int r = 156, cnt = 50;
        stone_map_[i].background_.setTexture(stone_bg);
        stone_map_[i].background_.setTextureRect(sf::IntRect(rand()%cnt*r, 0, r, r));
        
        stone_map_[i].text_.setTexture(stone_text);
    }

    stone_map_.init();
}
