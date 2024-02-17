//
// Created by Gianni on 9/01/2024.
//

#ifndef PLATFORMER_TEXTURE_MANAGER_HPP
#define PLATFORMER_TEXTURE_MANAGER_HPP

#include <SFML/Graphics/Texture.hpp>
#include "asset_manager.hpp"

class TextureManager : public AssetManager<TextureManager, sf::Texture>
{
    friend AssetManager;
private:
    static std::unique_ptr<sf::Texture> load(const std::string& file_name)
    {
        auto texture = std::make_unique<sf::Texture>();

        if (!texture->loadFromFile(file_name))
            throw std::runtime_error("TextureManager::load: Failed to load " + file_name);

        return texture;
    }
};

#endif //PLATFORMER_TEXTURE_MANAGER_HPP
