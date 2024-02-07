//
// Created by Gianni on 9/01/2024.
//

#ifndef PLATFORMER_FONT_MANAGER_HPP
#define PLATFORMER_FONT_MANAGER_HPP

#include <SFML/Graphics/Font.hpp>
#include "asset_manager.hpp"


class FontManager : public AssetManager<FontManager, sf::Font>
{
    friend AssetManager;
private:
    static std::unique_ptr<sf::Font> load(const std::string& file_name)
    {
        auto font = std::make_unique<sf::Font>();

        assert(font->loadFromFile(file_name));

        font->setSmooth(false);

        return font;
    }
};

#endif //PLATFORMER_FONT_MANAGER_HPP
