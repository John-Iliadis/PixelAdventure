//
// Created by Gianni on 14/01/2024.
//

#ifndef PLATFORMER_COLLISION_HPP
#define PLATFORMER_COLLISION_HPP

#include <iostream>
#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include "player.hpp"

namespace Collision
{
    bool point_vs_rect(const sf::Vector2f& point, const sf::FloatRect& rect);
    bool rect_vs_rect(const sf::FloatRect& rect1, const sf::FloatRect& rect2);
};


#endif //PLATFORMER_COLLISION_HPP
