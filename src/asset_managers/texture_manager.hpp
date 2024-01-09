//
// Created by Gianni on 9/01/2024.
//

#ifndef PLATFORMER_TEXTURE_MANAGER_HPP
#define PLATFORMER_TEXTURE_MANAGER_HPP

#include <SFML/Graphics/Texture.hpp>
#include "resourse_manager.hpp"

class TextureManager : public ResourceManager<TextureManager, sf::Texture>
{
    friend ResourceManager;
private:
    static std::unique_ptr<sf::Texture> load(const std::string& file_name)
    {
        auto texture = std::make_unique<sf::Texture>();
        if (!texture->loadFromFile(file_name))
            throw std::runtime_error("");

        return texture;
    }
};

#endif //PLATFORMER_TEXTURE_MANAGER_HPP
