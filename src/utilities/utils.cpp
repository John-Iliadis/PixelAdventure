//
// Created by Gianni on 9/01/2024.
//

#include "utils.hpp"


namespace utils
{
    float get_distance(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
    {
        return std::hypot(vec2.x - vec1.x, vec2.y - vec1.y);
    }

    void set_origin(sf::Sprite& sprite, Origin origin)
    {
        auto sprite_rect = sprite.getLocalBounds();

        switch (origin)
        {
            case Origin::TOP_LEFT:
                sprite.setOrigin(0, 0);
                break;

            case Origin::CENTER:
                sprite.setOrigin(static_cast<int>(sprite_rect.width / 2.f), static_cast<int>(sprite_rect.height / 2.f));
                break;

            case Origin::CENTER_BOTTOM:
                sprite.setOrigin(static_cast<int>(sprite_rect.width / 2.f), static_cast<int>(sprite_rect.height));
                break;

            default:
                assert(false);
        }
    }

    float to_radians(float degrees)
    {
        return degrees * M_PI / 180;
    }

    float to_degrees(float radians)
    {
        return radians * 180 / M_PI;
    }
}
