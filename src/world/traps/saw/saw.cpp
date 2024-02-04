//
// Created by Gianni on 1/02/2024.
//

#include "saw.hpp"


static const sf::Vector2f collider_size = {20, 20};

Saw::Saw(const sf::Texture& texture)
{
    m_animation = Animation(38, 38, 8, sf::milliseconds(30), true);

    m_sprite_collider.set_texture(texture);
    m_sprite_collider.set_collider_size(collider_size);
    m_sprite_collider.set_origin(Origin::CENTER);
}

void Saw::update(double dt)
{
    m_animation.update(dt);
    m_sprite_collider.set_texture_rect(m_animation.get_current_frame_rect());
}

sf::Rect<float> Saw::get_collider() const
{
    return m_sprite_collider.get_collider();
}
