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

            case Origin::CENTER_TOP:
                sprite.setOrigin(static_cast<int>(sprite_rect.width / 2.f), 0);
                break;

            case Origin::CENTER_LEFT:
                sprite.setOrigin(0, static_cast<int>(sprite_rect.height / 2.f));
                break;

            case Origin::CENTER_RIGHT:
                sprite.setOrigin(static_cast<int>(sprite_rect.width), static_cast<int>(sprite_rect.height / 2.f));
                break;

            default:
                assert(false);
        }
    }

    void center_text(sf::Text& text)
    {
        auto local_bounds = text.getLocalBounds();

        sf::Vector2i origin {
            static_cast<int>(local_bounds.left + local_bounds.width / 2.f),
            static_cast<int>(local_bounds.top + local_bounds.height / 2)
        };

        text.setOrigin(origin.x, origin.y);
    }

    float to_radians(float degrees)
    {
        return degrees * M_PI / 180;
    }

    float to_degrees(float radians)
    {
        return radians * 180 / M_PI;
    }

    int random(int min, int max)
    {
        static std::random_device m_random_device;
        static std::mt19937 m_engine(m_random_device());
        static std::uniform_int_distribution<int> m_int_distribution;

        if (min > max) std::swap(min, max);

        if (min != m_int_distribution.min() || max != m_int_distribution.max())
            m_int_distribution = std::uniform_int_distribution<int>(min, max);

        return m_int_distribution(m_engine);
    }
}
