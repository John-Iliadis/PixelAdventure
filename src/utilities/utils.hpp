//
// Created by Gianni on 9/01/2024.
//

#ifndef PLATFORMER_UTILS_HPP
#define PLATFORMER_UTILS_HPP

#include <windows.h>
#include <cstdint>
#include <stdexcept>
#include <cmath>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include "../world/enums.hpp"


namespace utils
{
    uint32_t get_max_refresh_rate();

    float get_distance(const sf::Vector2f& vec1, const sf::Vector2f& vec2);

    void set_origin_center(sf::Sprite& sprite);
    void set_origin_center(sf::Shape& shape);

    void set_origin_top_left(sf::Sprite& sprite);
    void set_origin_top_left(sf::Shape& shape);

    void set_origin_mid_bottom(sf::Sprite& sprite);
    void set_origin_mid_bottom(sf::Shape& shape);

    void flip_sprite(sf::Sprite& sprite);
}


#endif //PLATFORMER_UTILS_HPP
