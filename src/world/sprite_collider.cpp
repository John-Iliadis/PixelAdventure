//
// Created by Gianni on 22/01/2024.
//

#include "sprite_collider.hpp"


SpriteCollider::SpriteCollider()
{
    m_hit_box.setFillColor(sf::Color::Transparent);
    m_orientation = SpriteOrientation::FACES_RIGHT;
}

void SpriteCollider::set_texture(const sf::Texture &texture)
{
    m_sprite.setTexture(texture);
}

void SpriteCollider::set_texture_rect(const sf::IntRect &rect)
{
    m_sprite.setTextureRect(rect);
}

void SpriteCollider::set_hitbox_size(float width, float height)
{
    m_hit_box.setSize({width, height});
}

void SpriteCollider::set_orientation(SpriteOrientation orientation)
{
    if (m_orientation == orientation)
        return;

    m_orientation = orientation;
    utils::flip_sprite(m_sprite);
}

sf::Vector2f SpriteCollider::get_sprite_center() const
{
    auto rect = getTransform().transformRect(m_sprite.getGlobalBounds());

    return {rect.left + rect.width / 2.f,
            rect.top + rect.height / 2.f};
}

void SpriteCollider::set_origin_center()
{
    utils::set_origin_center(m_sprite);
    utils::set_origin_center(m_hit_box);
}

void SpriteCollider::set_origin_mid_bottom()
{
    utils::set_origin_mid_bottom(m_sprite);
    utils::set_origin_mid_bottom(m_hit_box);
}

sf::FloatRect SpriteCollider::get_hitbox() const
{
    return getTransform().transformRect(m_hit_box.getGlobalBounds());
}

void SpriteCollider::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(m_sprite, states);
    target.draw(m_hit_box, states);
}

SpriteOrientation SpriteCollider::get_orientation() const
{
    return m_orientation;
}
