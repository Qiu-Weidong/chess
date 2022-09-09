#include "game.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <iostream>

void Game::initFromFile(std::ifstream &in)
{

    rapidjson::IStreamWrapper isw(in);
    rapidjson::Document document;
    document.ParseStream(isw);

    padding_left_ = document["padding-left"].GetInt();
    padding_top_ = document["padding-top"].GetInt();

    rapidjson::Value &v = document["padding-right"];
    padding_right_ = v.IsNull() ? padding_left_ : v.GetInt();
    rapidjson::Value &v2 = document["padding-bottom"];
    padding_bottom_ = v2.IsNull() ? padding_top_ : v.GetInt();

    stone_radius_ = document["stone-radius"].GetInt();

    const int window_width = stone_radius_ * 2 * 9 + padding_left_ + padding_right_;
    const int window_height = stone_radius_ * 2 * 10 + padding_top_ + padding_bottom_;
    // 设置标题
    rapidjson::Value &title_value = document["title"];
    std::string title = title_value.IsNull() ? "中国象棋对战" : title_value.GetString();
    // std::cout << window_width << ", " << window_height << std::endl;
    window_.create(sf::VideoMode(window_width, window_height), sf::String::fromUtf8(title.begin(), title.end()));

    rapidjson::Value &positon = document["window-positon"];
    if (!positon.IsNull())
    {
        rapidjson::Value &v = positon["left"];
        const int left = v.IsNull() ? 340 : v.GetInt();
        rapidjson::Value &v2 = positon["top"];
        const int top = v2.IsNull() ? 0 : v2.GetInt();
        // std::cout << left << ", " << top << std::endl;
        window_.setPosition(sf::Vector2i(left, top));
    }
    else
    {
        // 给一个默认位置
        window_.setPosition(sf::Vector2i(340, 0));
    }

    // 加载棋盘
    const std::string url = document["img-dir"].GetString();
    std::string board_url = url + document["board-img"].GetString();
    board_.setTexture(getTexture(board_url));
    board_.setPosition(padding_left_ + stone_radius_, padding_top_ + stone_radius_);
    float scale = stone_radius_ / 70.0f;
    board_.setScale(scale, scale);

    // 加载棋盘背景
    std::string board_background_url = url + document["board-background"].GetString();
    board_background_.setTexture(getTexture(board_background_url));
}

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

    window_.draw(board_background_);
    window_.draw(board_);

    window_.display();
}

