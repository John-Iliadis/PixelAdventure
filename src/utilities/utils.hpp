//
// Created by Gianni on 9/01/2024.
//

#ifndef PLATFORMER_UTILS_HPP
#define PLATFORMER_UTILS_HPP

#include <cmath>
#include <cassert>
#include <limits>
#include <random>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include "../enums/origin.hpp"


namespace utils
{
    float get_distance(const sf::Vector2f& vec1, const sf::Vector2f& vec2);

    void set_origin(sf::Sprite& sprite, Origin origin);
    void set_origin(sf::Text& text, Origin origin);

    float to_radians(float degrees);
    float to_degrees(float radians);

    int random(int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max());
}


#endif //PLATFORMER_UTILS_HPP
