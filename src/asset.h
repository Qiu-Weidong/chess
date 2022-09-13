#ifndef CHESS_ASSET_H_
#define CHESS_ASSET_H_
#include <map>
#include <cassert>
#include "SFML/Graphics.hpp"

class Asset {
private:
    std::map<std::string, sf::Texture> textures_;

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
};
#endif // CHESS_ASSET_H_
