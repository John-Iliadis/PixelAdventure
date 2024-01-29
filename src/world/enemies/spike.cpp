//
// Created by Gianni on 29/01/2024.
//

#include "spike.hpp"


static const sf::Vector2f collider_size = {16, 7};

Spike::Spike(const sf::Texture &texture, const sf::Vector2f &pos, int rotation)
{
    m_sprite_collider.set_texture(texture);
    m_sprite_collider.set_rotation(rotation);
    m_sprite_collider.set_collider_size(collider_size.x, collider_size.y);
    m_sprite_collider.set_origin(Origin::CENTER_BOTTOM);

    sf::Vector2f sprite_size = m_sprite_collider.get_sprite_rect().getSize();

    switch (rotation)
    {
        case 0:
            m_sprite_collider.set_position(pos.x + sprite_size.x / 2, pos.y + sprite_size.y);
            break;
        case 90:
            m_sprite_collider.set_position(pos.x , pos.y + sprite_size.y / 2);
            break;
        case 180:
            m_sprite_collider.set_position(pos.x + sprite_size.x / 2, pos.y);
            break;
        case 270:
            m_sprite_collider.set_position(pos.x + sprite_size.x, pos.y + sprite_size.y / 2.f);
            break;
        default:
            throw std::runtime_error("Spike::Spike: Spike must have orthogonal rotation only");
    }
}

sf::Rect<float> Spike::get_collider() const
{
    return m_sprite_collider.get_collider();
}
