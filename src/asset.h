#ifndef CHESS_ASSET_H_
#define CHESS_ASSET_H_
#include <map>
#include <cassert>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

class Asset {
private:
    std::map<std::string, sf::Texture> textures_;
    std::map<std::string, sf::Font> fonts_;
    std::map<std::string, sf::SoundBuffer> sounds_;

    static Asset * p_asset_;

    Asset() = default;
    Asset(const Asset &) = delete;
    Asset(Asset &&) = delete;
    Asset &operator=(const Asset &) = delete;
    Asset &operator=(Asset &&) = delete;

public:
    static Asset &getInstanct() {
        if(p_asset_ == nullptr) p_asset_ = new Asset();
        return *p_asset_;
    }

    sf::Texture &getTexture(const std::string &url) {
        const auto it = textures_.find(url);
        if (it != textures_.end())
            return it->second;
        sf::Texture &texture = textures_[url];
        assert(texture.loadFromFile(url));
        return texture;
    }

    sf::Font &getFont(const std::string &url) {
        const auto it = fonts_.find(url);
        if(it != fonts_.end()) 
            return it->second;
        sf::Font &font = fonts_[url];
        assert(font.loadFromFile(url));
        return font;
    }

    sf::SoundBuffer &getSound(const std::string &url) {
        const auto it = sounds_.find(url);
        if(it != sounds_.end()) 
            return it->second;
        sf::SoundBuffer &sound = sounds_[url];
        assert(sound.loadFromFile(url));
        return sound;
    }
};
#endif // CHESS_ASSET_H_
