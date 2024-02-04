//
// Created by Gianni on 4/02/2024.
//

#include "fruit.hpp"


static const sf::Vector2f collider_size = {18, 20};

Fruit::Fruit(const sf::Texture &texture, const sf::Vector2f &position)
{
    m_animation = Animation(32, 32, 17, sf::milliseconds(50), true);

    m_fruit.set_texture(texture);
    m_fruit.set_position(position);
    m_fruit.set_collider_size(collider_size);
    m_fruit.set_origin(Origin::CENTER);
}

void Fruit::update(double dt)
{
    m_animation.update(dt);
    m_fruit.set_texture_rect(m_animation.get_current_frame_rect());
}

sf::Rect<float> Fruit::get_collider() const
{
    return m_fruit.get_collider();
}

void Fruit::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_fruit);
}

sf::Vector2f Fruit::get_position() const
{
    return m_fruit.get_position();
}
