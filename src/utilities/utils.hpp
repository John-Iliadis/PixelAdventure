//
// Created by Gianni on 9/01/2024.
//

#ifndef PLATFORMER_UTILS_HPP
#define PLATFORMER_UTILS_HPP

#include <windows.h>
#include <cstdint>
#include <stdexcept>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "../world/enums.hpp"


namespace utils
{
    uint32_t get_max_refresh_rate();

    void set_origin_center(sf::Sprite& sprite);
    void set_origin_center(sf::RectangleShape& shape);

    void set_origin_top_left(sf::Sprite& sprite);
    void set_origin_top_left(sf::RectangleShape& shape);

    void set_origin_mid_bottom(sf::Sprite& sprite);
    void set_origin_mid_bottom(sf::RectangleShape& shape);

    void flip_sprite(sf::Sprite& sprite);
}


#endif //PLATFORMER_UTILS_HPP
