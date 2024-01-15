//
// Created by Gianni on 14/01/2024.
//

#include "collision.hpp"


namespace Collision
{
    bool point_vs_rect(const sf::Vector2f& point, const sf::FloatRect& rect)
    {
        return (point.x >= rect.left && point.x < (rect.left + rect.width) &&
                point.y >= rect.top && point.y < (rect.top + rect.height));
    }

    bool rect_vs_rect(const sf::FloatRect& rect1, const sf::FloatRect& rect2)
    {
        return (rect1.left < (rect2.left + rect2.width) && rect1.top < (rect2.top + rect2.height) &&
                (rect1.left + rect1.width) > rect2.left && (rect1.top + rect1.height) > rect2.top);
    }
};
