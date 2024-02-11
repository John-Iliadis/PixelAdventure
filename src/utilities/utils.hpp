//
// Created by Gianni on 9/01/2024.
//

#ifndef PLATFORMER_UTILS_HPP
#define PLATFORMER_UTILS_HPP

#include <cmath>
#include <cassert>
#include <limits>
#include <random>
#include <unordered_map>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "../enums/origin.hpp"


namespace utils
{
    float get_distance(const sf::Vector2f& vec1, const sf::Vector2f& vec2);

    void set_origin(sf::Sprite& sprite, Origin origin);
    void set_origin(sf::Text& text, Origin origin);

    float to_radians(float degrees);
    float to_degrees(float radians);

    int random(int min = std::numeric_limits<int>::min(), int max = std::numeric_limits<int>::max());

    std::string key_to_string(sf::Keyboard::Key key);
    sf::Keyboard::Key string_to_key(const std::string& str);
}


#endif //PLATFORMER_UTILS_HPP
