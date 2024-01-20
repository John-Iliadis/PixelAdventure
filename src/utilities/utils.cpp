//
// Created by Gianni on 9/01/2024.
//

#include "utils.hpp"


uint32_t get_max_refresh_rate()
{
    DEVMODE dev_mode;
    memset(&dev_mode, 0, sizeof(DEVMODE));
    dev_mode.dmSize = sizeof(DEVMODE);

    if (EnumDisplaySettings(nullptr, ENUM_CURRENT_SETTINGS, &dev_mode) == TRUE)
        return dev_mode.dmDisplayFrequency;
    else
        throw std::runtime_error("get_max_refresh_rate() - Failed to retrieve monitor refresh rate\n");
}

void set_origin_center(sf::Sprite& sprite)
{
    auto rect = sprite.getLocalBounds();

    sprite.setOrigin(rect.width / 2.f, rect.height / 2.f);
}

void set_origin_top_left(sf::Sprite& sprite)
{
    sprite.setOrigin(0, 0);
}

void set_origin_mid_bottom(sf::Sprite& sprite)
{
    auto rect = sprite.getLocalBounds();
    sprite.setOrigin(rect.width / 2.f, rect.height);
}

void set_origin_mid_bottom(sf::RectangleShape& shape)
{
    auto rect = shape.getLocalBounds();
    shape.setOrigin(rect.width / 2.f, rect.height);
}

void flip_sprite_x(sf::Sprite& sprite, bool facing_right)
{
    auto rect = sprite.getTextureRect();

    if (facing_right)
    {
        rect = {0, 0, -rect.width, rect.height};
    }
    else
    {
        rect = {rect.width, 0, -rect.width, rect.height};
    }

    sprite.setTextureRect(rect);
}
